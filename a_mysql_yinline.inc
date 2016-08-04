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

stock mysql_tquery_inline(MySQL:handle, const query[], callback:inline_callback, const format[], {Float,_}:...)
{
	new cb_data[E_CALLBACK_DATA];
	if(!Callback_Get(inline_callback, cb_data))
		return false;
	
	new cb_format[33] = "ad";
	strcat(cb_format, format);
	
	return mysql_tquery(handle, query, "__MysqlInlineProcessCallback", format, cb_data, sizeof cb_data);
}

forward __MysqlInlineProcessCallback(cb_data[E_CALLBACK_DATA], cb_data_size);
public __MysqlInlineProcessCallback(cb_data[E_CALLBACK_DATA], cb_data_size)
{
	
}
