dnl $Id$
dnl config.m4 for extension zhaoyu

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(zhaoyu, for zhaoyu support,
dnl Make sure that the comment is aligned:
dnl [  --with-zhaoyu             Include zhaoyu support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(zhaoyu, whether to enable zhaoyu support,
dnl Make sure that the comment is aligned:
[  --enable-zhaoyu           Enable zhaoyu support])

if test "$PHP_ZHAOYU" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-zhaoyu -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/zhaoyu.h"  # you most likely want to change this
  dnl if test -r $PHP_ZHAOYU/$SEARCH_FOR; then # path given as parameter
  dnl   ZHAOYU_DIR=$PHP_ZHAOYU
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for zhaoyu files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       ZHAOYU_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$ZHAOYU_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the zhaoyu distribution])
  dnl fi

  dnl # --with-zhaoyu -> add include path
  dnl PHP_ADD_INCLUDE($ZHAOYU_DIR/include)

  dnl # --with-zhaoyu -> check for lib and symbol presence
  dnl LIBNAME=zhaoyu # you may want to change this
  dnl LIBSYMBOL=zhaoyu # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $ZHAOYU_DIR/$PHP_LIBDIR, ZHAOYU_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_ZHAOYULIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong zhaoyu lib version or lib not found])
  dnl ],[
  dnl   -L$ZHAOYU_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(ZHAOYU_SHARED_LIBADD)

  PHP_NEW_EXTENSION(zhaoyu, zhaoyu.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
