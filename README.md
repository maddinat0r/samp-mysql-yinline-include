# y_inline callbacks for BlueG's MySQL plugin
This is a SA-MP PAWN include which adds support for y_inline callbacks to be used with BlueG's MySQL plugin version R40 and higher. Simply include it in your gamemode and/or filterscript/s and you're ready to go.

## Available functions:
```pawn
mysql_tquery_inline(MySQL:handle, const query[], callback:Callback, const format[], {Float,_}:...);
mysql_pquery_inline(MySQL:handle, const query[], callback:Callback, const format[], {Float,_}:...);

orm_select_inline(ORM:id, callback:Callback, const format[], {Float,_}:...);
orm_update_inline(ORM:id, callback:Callback, const format[], {Float,_}:...);
orm_insert_inline(ORM:id, callback:Callback, const format[], {Float,_}:...);
orm_delete_inline(ORM:id, callback:Callback, const format[], {Float,_}:...);
orm_load_inline(ORM:id, callback:Callback, const format[], {Float,_}:...);
orm_save_inline(ORM:id, callback:Callback, const format[], {Float,_}:...);
```
Every function returns `0` in case of an error.

## Example
```pawn
#include <a_samp>
#include <a_mysql>
#include <a_mysql_yinline>

new MySQL:g_Mysql;

main() { }

public OnGameModeInit()
{
	inline InlineCallback(number, Float:flt, string:str[])
	{
		new value;
		if(!cache_get_value_int(0, 0, value))
			printf("some error happened, check the MySQL log!");
	}
	
	new ret = mysql_tquery_inline(
				g_Mysql, "SELECT 1", 
				using inline InlineCallback, "dfs", 23, 3.1424512, "banana");
		
	if(!ret)
		printf("some error happened, check the MySQL log!");
	
	return 1;
}

```
