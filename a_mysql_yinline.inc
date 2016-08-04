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
