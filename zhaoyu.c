/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_zhaoyu.h"
#include "Zend/zend_types.h"
#include "Zend/zend_alloc.h"

/* If you declare any globals in php_zhaoyu.h uncomment this:
 *
 */
ZEND_DECLARE_MODULE_GLOBALS(zhaoyu)


/* True global resources - no need for thread safety here */
static int le_zhaoyu;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("zhaoyu.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_zhaoyu_globals, zhaoyu_globals)
    STD_PHP_INI_ENTRY("zhaoyu.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_zhaoyu_globals, zhaoyu_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_zhaoyu_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(zhaoyu_get_all_classes)
{

	array_init(return_value);

	int num = EG(class_table)->nNumOfElements;

	for (int i = 0; i < num; i++)
	{
		Bucket *arr = (EG(class_table)->arData + i);
		add_next_index_string(return_value,arr->key->val);
	}
}
/* }}} */



PHP_FUNCTION(zhaoyu_get_all_functions)
{
	array_init(return_value);

	int num = EG(function_table)->nNumOfElements;

	for (int i = 0; i < num; i++)
	{
		Bucket *arr = (EG(function_table)->arData + i);
		add_next_index_string(return_value,arr->key->val);
	}
}




PHP_FUNCTION(zhaoyu_get_all_global_vars)
{

	array_init(return_value);



	int num = EG(symbol_table).nNumOfElements;

	for (int i = 0; i < num; i++)
	{
		Bucket *arr = (EG(symbol_table).arData + i);
		add_next_index_string(return_value,arr->key->val);
	}
}


PHP_FUNCTION(zhaoyu_set_autofunction)
{
	zend_string *name;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"S", &name) == FAILURE) {
		RETURN_NULL();
	}

	zend_function *spl_func_ptr = zend_hash_find_ptr(EG(function_table), name);
	if (spl_func_ptr == NULL)
	{
		php_printf("not found %s function! \n" ,name);
		zend_string_release(name);
		RETURN_NULL();
	}

	EG(autoload_func) =	spl_func_ptr;

//	if (EG(in_autoload) == NULL) {
//		ALLOC_HASHTABLE(EG(in_autoload));
//		zend_hash_init(EG(in_autoload), 8, NULL, NULL, 0);
//	}
//
//	if (zend_hash_add_empty_element(EG(in_autoload), name) == NULL) {
//		zend_string_release(name);
//		RETURN_NULL();
//	}

	zend_string_release(name);
	RETURN_TRUE;
}

/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.

static void php_zhaoyu_init_globals(zend_zhaoyu_globals *zhaoyu_globals)
{
	printf("aaaaaaaaaaaaa");
}
*/



/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(zhaoyu)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/



	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(zhaoyu)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(zhaoyu)
{
#if defined(COMPILE_DL_ZHAOYU) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(zhaoyu)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(zhaoyu)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "zhaoyu support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


ZEND_BEGIN_ARG_INFO(arginfo_set_autofunction, 0)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()
/* {{{ zhaoyu_functions[]
 *
 * Every user visible function must have an entry in zhaoyu_functions[].
 */
const zend_function_entry zhaoyu_functions[] = {
	PHP_FE(zhaoyu_get_all_classes,	NULL)		/* For testing, remove later. */
	PHP_FE(zhaoyu_get_all_functions,	NULL)
	PHP_FE(zhaoyu_get_all_global_vars,	NULL)
	PHP_FE(zhaoyu_set_autofunction,	arginfo_set_autofunction)
	PHP_FE_END	/* Must be the last line in zhaoyu_functions[] */
};
/* }}} */

/* {{{ zhaoyu_module_entry
 */
zend_module_entry zhaoyu_module_entry = {
	STANDARD_MODULE_HEADER,
	"zhaoyu",
	zhaoyu_functions,
	PHP_MINIT(zhaoyu),
	PHP_MSHUTDOWN(zhaoyu),
	PHP_RINIT(zhaoyu),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(zhaoyu),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(zhaoyu),
	PHP_ZHAOYU_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_ZHAOYU
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(zhaoyu)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
