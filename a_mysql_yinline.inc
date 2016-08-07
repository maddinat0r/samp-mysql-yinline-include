/**
 * y_inline support include for BlueG's MySQL plugin
 */

#if defined a_mysql_yinline_included
	#endinput
#endif
#define a_mysql_yinline_included

#tryinclude <a_mysql>

#if !defined mysql_tquery
	#error You have to include the MySQL plugin include before this one!
#endif

#tryinclude <YSI_Coding\y_inline>
#tryinclude <YSI\y_inline>

#if !defined _INC_y_inline
	#error You have to include the y_inline include before this one!
#endif

/*
native mysql_tquery_inline(MySQL:handle, const query[], callback:Callback, const format[], {Float,_}:...);
native mysql_pquery_inline(MySQL:handle, const query[], callback:Callback, const format[], {Float,_}:...);
*/

/*
native orm_select_inline(ORM:id, callback:Callback, format[], {Float,_}:...);
native orm_update_inline(ORM:id, callback:Callback, format[], {Float,_}:...);
native orm_insert_inline(ORM:id, callback:Callback, format[], {Float,_}:...);
native orm_delete_inline(ORM:id, callback:Callback, format[], {Float,_}:...);
native orm_load_inline(ORM:id, callback:Callback, format[], {Float,_}:...);
native orm_save_inline(ORM:id, callback:Callback, format[], {Float,_}:...);
*/

forward __int_MysqlInline_Invoke();
public __int_MysqlInline_Invoke()
{
	mysql_tquery(MYSQL_INVALID_HANDLE, "");
}

stock mysql_tquery_inline(MySQL:handle, const query[], callback:inline_callback, const format[] = "", {Float,_}:...)
{
	const num_const_args = 4;
	const num_const_args_native = 7;
	
	new cb_data[E_CALLBACK_DATA];
	if(!Callback_Get(inline_callback, cb_data))
		return false;
	
	new cb_format[33] = "sad";
	strcat(cb_format, format);
	
	new args_count = numargs();
	new args_count_byte = args_count * 4;
	new args_count_native_byte = (args_count - num_const_args + num_const_args_native) * 4;
	new inline_res_cb[] = "__MysqlInlineProcessCallback";
	new cb_data_size = sizeof cb_data;
	
	new first_vparam_addr;
	
	//write address of 'format' into 'first_vparam_addr'
	#emit ADDR.PRI format // PRI = FRM + format
	#emit STOR.S.pri first_vparam_addr //[FRM + first_vparam_addr] = PRI
	
	new param_addr = first_vparam_addr + (args_count_byte - num_const_args * 4);
	for (; param_addr > first_vparam_addr; param_addr -= 4)
	{
		//load vararg into PRI
		#emit LOAD.S.pri param_addr //PRI = [FRM + param_addr]
		
		//variable arguments are always references, so we have 
		//to dereference it to get the actual value
		#emit LOAD.I //PRI = [PRI]
		
		#emit PUSH.pri
	}
	
	
	#emit PUSH.ADR cb_data_size
	#emit PUSH.ADR cb_data
	#emit PUSH.S format
	#emit PUSH.ADR cb_format
	#emit PUSH.ADR inline_res_cb
	#emit PUSH.S query
	#emit PUSH.S handle
	
	#emit PUSH.S args_count_native_byte
	
	#emit SYSREQ.C mysql_tquery
	
	#emit STACK 4 //args_count_native_byte
	
	for(new i = args_count_native_byte / 4; i > 0; --i)
	{
		#emit STACK 4
	}
	return 1;
}

forward __MysqlInlineProcessCallback(const params_format[], cb_data[E_CALLBACK_DATA], cb_data_size, ...);
public __MysqlInlineProcessCallback(const params_format[], cb_data[E_CALLBACK_DATA], cb_data_size, ...)
{
	const num_const_args = 3;
	const num_const_args_native = 1;
	
	new args_count = numargs();
	new args_count_byte = args_count * 4;
	new args_count_native_byte = (args_count - num_const_args + num_const_args_native) * 4;

	new first_vparam_addr;

	//write address of 'cb_data_size' into 'first_vparam_addr'
	#emit ADDR.PRI cb_data_size // PRI = FRM + cb_data_size
	#emit STOR.S.pri first_vparam_addr //[FRM + first_vparam_addr] = PRI
	
	new param_addr = first_vparam_addr + (args_count_byte - num_const_args * 4);
	new idx = strlen(params_format);
	for (; param_addr > first_vparam_addr; param_addr -= 4)
	{
		//variable arguments are always references, however,
		//we DON'T dereference here because we told the MySQL plugin
		//via the callback format parameter, that we pushed literal
		//values, NOT references
		//...unless the parameter is a string/array, then we
		//have to dereference it
		
		idx--;
		if(params_format[idx] == 's' || params_format[idx] == 'a')
		{
			#emit LOAD.S.pri param_addr //PRI = [FRM + param_addr]
			#emit LOAD.I //PRI = [PRI]
			#emit PUSH.pri
		}
		else
		{
			#emit PUSH.S param_addr
		}
	}
	
	#emit PUSH.S cb_data
	
	#emit PUSH.S args_count_native_byte
	
	#emit CALL Callback_Call
	
	Callback_Release(cb_data);
	return 1;
}
