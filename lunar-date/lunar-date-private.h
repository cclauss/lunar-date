/* vi: set sw=4 ts=4 expandtab: */
/*
 * lunar-date-private.h: This file is part of liblunar.
 *
 * Copyright (C) 2009-2021 yetist <yetist@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, see <http://www.gnu.org/licenses/>.
 * */

#ifndef __LUNAR_DATE_PRIVATE_H__
#define __LUNAR_DATE_PRIVATE_H__  1

#if HAVE_CONFIG_H
#include <config.h>
#endif
#include <glib.h>
#include <glib/gi18n-lib.h>
#include "lunar-date-utils.h"

G_BEGIN_DECLS

#define BEGIN_YEAR	1900	/* Note that LC1900.1.1 is SC1900.1.31 */
#define NUM_OF_YEARS 201
#define NUM_OF_MONTHS 13

long years_info[NUM_OF_YEARS] = {
    /* encoding:
     *
     * b      bbbbbbbbbbbb bbbb
     * bit#	1 111111000000 0000
     *      6 543210987654 3210
     *      . ............ ....
     * month# 000000000111
     *      M 123456789012 L

     b_j = 1 for long month, b_j = 0 for short month
     L is the leap month of the year if 1<=L<=12; NO leap month if L = 0.
     The leap month (if exists) is long one iff M = 1.
     */
    0x04bd8,	/* 1900 */
    0x04ae0, 0x0a570, 0x054d5, 0x0d260, 0x0d950,	/* 1905 */
    0x16554, 0x056a0, 0x09ad0, 0x055d2, 0x04ae0,	/* 1910 */
    0x0a5b6, 0x0a4d0, 0x0d250, 0x1d255, 0x0b540,	/* 1915 */
    0x0d6a0, 0x0ada2, 0x095b0, 0x14977, 0x04970,	/* 1920 */
    0x0a4b0, 0x0b4b5, 0x06a50, 0x06d40, 0x1ab54,	/* 1925 */
    0x02b60, 0x09570, 0x052f2, 0x04970, 0x06566,	/* 1930 */
    0x0d4a0, 0x0ea50, 0x06e95, 0x05ad0, 0x02b60,	/* 1935 */
    0x186e3, 0x092e0, 0x1c8d7, 0x0c950, 0x0d4a0,	/* 1940 */
    0x1d8a6, 0x0b550, 0x056a0, 0x1a5b4, 0x025d0,	/* 1945 */
    0x092d0, 0x0d2b2, 0x0a950, 0x0b557, 0x06ca0,	/* 1950 */
    0x0b550, 0x15355, 0x04da0, 0x0a5d0, 0x14573,	/* 1955 */
    0x052d0, 0x0a9a8, 0x0e950, 0x06aa0, 0x0aea6,	/* 1960 */
    0x0ab50, 0x04b60, 0x0aae4, 0x0a570, 0x05260,	/* 1965 */
    0x0f263, 0x0d950, 0x05b57, 0x056a0, 0x096d0,	/* 1970 */
    0x04dd5, 0x04ad0, 0x0a4d0, 0x0d4d4, 0x0d250,	/* 1975 */
    0x0d558, 0x0b540, 0x0b5a0, 0x195a6, 0x095b0,	/* 1980 */
    0x049b0, 0x0a974, 0x0a4b0, 0x0b27a, 0x06a50,	/* 1985 */
    0x06d40, 0x0af46, 0x0ab60, 0x09570, 0x04af5,	/* 1990 */
    0x04970, 0x064b0, 0x074a3, 0x0ea50, 0x06b58,	/* 1995 */
    0x05ac0, 0x0ab60, 0x096d5, 0x092e0, 0x0c960,	/* 2000 */
    0x0d954, 0x0d4a0, 0x0da50, 0x07552, 0x056a0,	/* 2005 */
    0x0abb7, 0x025d0, 0x092d0, 0x0cab5, 0x0a950,	/* 2010 */
    0x0b4a0, 0x0baa4, 0x0ad50, 0x055d9, 0x04ba0,	/* 2015 */
    0x0a5b0, 0x15176, 0x052b0, 0x0a930, 0x07954,	/* 2020 */
    0x06aa0, 0x0ad50, 0x05b52, 0x04b60, 0x0a6e6,	/* 2025 */
    0x0a4e0, 0x0d260, 0x0ea65, 0x0d530, 0x05aa0,	/* 2030 */
    0x076a3, 0x096d0, 0x04afb, 0x04ad0, 0x0a4d0,	/* 2035 */
    0x1d0b6, 0x0d250, 0x0d520, 0x0dd45, 0x0b5a0,	/* 2040 */
    0x056d0, 0x055b2, 0x049b0, 0x0a577, 0x0a4b0,	/* 2045 */
    0x0aa50, 0x1b255, 0x06d20, 0x0ada0, 0x14b63,	/* 2050 */
    0x09370, 0x049f8, 0x04970, 0x064b0, 0x168a6,	/* 2055 */
    0x0ea50, 0x06b20, 0x1a6c4, 0x0aae0, 0x0a2e0,	/* 2060 */
    0x0d2e3, 0x0c960, 0x0d557, 0x0d4a0, 0x0da50,	/* 2065 */
    0x05d55, 0x056a0, 0x0a6d0, 0x055d4, 0x052d0,	/* 2070 */
    0x0a9b8, 0x0a950, 0x0b4a0, 0x0b6a6, 0x0ad50,	/* 2075 */
    0x055a0, 0x0aba4, 0x0a5b0, 0x052b0, 0x0b273,	/* 2080 */
    0x06930, 0x07337, 0x06aa0, 0x0ad50, 0x14b55,	/* 2085 */
    0x04b60, 0x0a570, 0x054e4, 0x0d160, 0x0e968,	/* 2090 */
    0x0d520, 0x0daa0, 0x16aa6, 0x056d0, 0x04ae0,	/* 2095 */
    0x0a9d4, 0x0a2d0, 0x0d150, 0x0f252, 0x0d520 	/* 2100 */

};

/*
   In "4-column" calculation, a "mingli" (fortune-telling) calculation,
   the beginning of a month is not the first day of the month as in
   the Lunar Calendar; it is instead governed by "jie2" (festival).
   Interestingly, in the Solar calendar, a jie always comes around certain
   day. For example, the jie "li4chun1" (beginning of spring) always comes
   near Feburary 4 of the Solar Calendar.

   Meaning of array fest:
   Each element, fest[i][j] stores the jie day (in term of the following Solar
   month) of the lunar i-th year, j-th month.
   For example, in 1992, fest[92][0] is 4, that means the jie "li4chun1"
   (beginning of spring) is on Feb. 4, 1992; fest[92][11] is 5, that means
   the jie of the 12th lunar month is on Jan. 5, 1993.
   */

static gchar fest[NUM_OF_YEARS][12] = {
    {4, 6, 5, 6, 6, 7, 8, 8, 9, 8, 7, 6},	/* 1900 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1901 */
    {5, 6, 6, 6, 7, 8, 8, 8, 9, 8, 8, 6},	/* 1902 */
    {5, 7, 6, 7, 7, 8, 9, 9, 9, 8, 8, 7},	/* 1903 */
    {5, 6, 5, 6, 6, 7, 8, 8, 9, 8, 7, 6},	/* 1904 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1905 */
    {5, 6, 6, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1906 */
    {5, 7, 6, 7, 7, 8, 9, 9, 9, 8, 8, 7},	/* 1907 */
    {5, 6, 5, 6, 6, 7, 8, 8, 9, 8, 7, 6},	/* 1908 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1909 */
    {5, 6, 6, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1910 */
    {5, 7, 6, 7, 7, 8, 9, 9, 9, 8, 8, 7},	/* 1911 */
    {5, 6, 5, 6, 6, 7, 8, 8, 9, 8, 7, 6},	/* 1912 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1913 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1914 */
    {5, 6, 6, 6, 7, 8, 8, 9, 9, 8, 8, 6},	/* 1915 */
    {5, 6, 5, 6, 6, 7, 8, 8, 8, 8, 7, 6},	/* 1916 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 8, 7, 6},	/* 1917 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1918 */
    {5, 6, 6, 6, 7, 8, 8, 9, 9, 8, 8, 6},	/* 1919 */
    {5, 6, 5, 6, 6, 7, 8, 8, 8, 8, 7, 6},	/* 1920 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 9, 7, 6},	/* 1921 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1922 */
    {5, 6, 6, 6, 7, 8, 8, 9, 9, 8, 8, 6},	/* 1923 */
    {5, 6, 5, 6, 6, 7, 8, 8, 8, 8, 7, 6},	/* 1924 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 8, 7, 6},	/* 1925 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1926 */
    {5, 6, 6, 6, 7, 8, 8, 8, 9, 8, 8, 6},	/* 1927 */
    {5, 6, 5, 6, 6, 7, 8, 8, 8, 7, 7, 6},	/* 1928 */
    {4, 6, 5, 6, 6, 7, 8, 8, 9, 8, 7, 6},	/* 1929 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1930 */
    {5, 6, 6, 6, 7, 8, 8, 8, 9, 8, 8, 6},	/* 1931 */
    {5, 6, 5, 6, 6, 7, 8, 8, 8, 7, 7, 6},	/* 1932 */
    {4, 6, 5, 6, 6, 7, 8, 8, 9, 8, 7, 6},	/* 1933 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1934 */
    {5, 6, 6, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1935 */
    {5, 6, 5, 6, 6, 7, 8, 8, 8, 7, 7, 6},	/* 1936 */
    {4, 6, 5, 6, 6, 7, 8, 8, 9, 8, 7, 6},	/* 1937 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1938 */
    {5, 6, 6, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1939 */
    {5, 6, 5, 6, 6, 7, 8, 8, 8, 7, 7, 6},	/* 1940 */
    {4, 6, 5, 6, 6, 7, 8, 8, 9, 8, 7, 6},	/* 1941 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1942 */
    {5, 6, 6, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1943 */
    {5, 6, 5, 5, 6, 7, 8, 8, 8, 7, 7, 6},	/* 1944 */
    {4, 6, 5, 6, 6, 7, 8, 8, 8, 8, 7, 6},	/* 1945 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1946 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1947 */
    {5, 5, 5, 5, 6, 7, 7, 8, 8, 7, 7, 5},	/* 1948 */
    {4, 6, 5, 6, 6, 7, 8, 8, 8, 8, 7, 6},	/* 1949 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1950 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1951 */
    {5, 5, 5, 5, 6, 7, 7, 8, 8, 7, 7, 5},	/* 1952 */
    {4, 6, 5, 6, 6, 7, 8, 8, 8, 8, 7, 6},	/* 1953 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 8, 7, 6},	/* 1954 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1955 */
    {5, 5, 5, 5, 6, 7, 7, 8, 8, 7, 7, 5},	/* 1956 */
    {4, 6, 5, 6, 6, 7, 8, 8, 8, 8, 7, 6},	/* 1957 */
    {4, 6, 5, 6, 6, 7, 8, 8, 9, 8, 7, 6},	/* 1958 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1959 */
    {5, 5, 5, 5, 6, 7, 7, 7, 8, 7, 7, 5},	/* 1960 */
    {4, 6, 5, 6, 6, 7, 8, 8, 8, 7, 7, 6},	/* 1961 */
    {4, 6, 5, 6, 6, 7, 8, 8, 9, 8, 7, 6},	/* 1962 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1963 */
    {5, 5, 5, 5, 6, 7, 7, 7, 8, 7, 7, 5},	/* 1964 */
    {4, 6, 5, 6, 6, 7, 8, 8, 8, 7, 7, 6},	/* 1965 */
    {4, 6, 5, 6, 6, 7, 8, 8, 9, 8, 7, 6},	/* 1966 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1967 */
    {5, 5, 5, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 1968 */
    {4, 6, 5, 6, 6, 7, 8, 8, 8, 7, 7, 6},	/* 1969 */
    {4, 6, 5, 6, 6, 7, 8, 8, 9, 8, 7, 6},	/* 1970 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1971 */
    {5, 5, 5, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 1972 */
    {4, 6, 5, 5, 6, 7, 8, 8, 8, 7, 7, 6},	/* 1973 */
    {4, 6, 5, 6, 6, 7, 8, 8, 9, 8, 7, 6},	/* 1974 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1975 */
    {5, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 1976 */
    {4, 6, 5, 5, 6, 7, 7, 8, 8, 7, 7, 6},	/* 1977 */
    {4, 6, 5, 6, 6, 7, 8, 8, 8, 8, 7, 6},	/* 1978 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1979 */
    {5, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 1980 */
    {4, 6, 5, 5, 6, 7, 7, 8, 8, 7, 7, 6},	/* 1981 */
    {4, 6, 5, 6, 6, 7, 8, 8, 8, 8, 7, 6},	/* 1982 */
    {4, 6, 5, 6, 6, 8, 8, 8, 9, 8, 8, 6},	/* 1983 */
    {4, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 1984 */
    {5, 5, 5, 5, 5, 8, 7, 7, 8, 7, 7, 5},	/* 1985 */
    {4, 6, 5, 6, 6, 7, 8, 8, 8, 8, 7, 6},	/* 1986 */
    {4, 6, 5, 6, 6, 7, 8, 8, 9, 8, 7, 6},	/* 1987 */
    {4, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 1988 */
    {5, 5, 5, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 1989 */
    {4, 6, 5, 6, 6, 7, 8, 8, 8, 8, 7, 6},	/* 1990 */
    {4, 6, 5, 6, 6, 7, 8, 8, 9, 8, 7, 6},	/* 1991 */
    {4, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 1992 */
    {5, 5, 5, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 1993 */
    {4, 6, 5, 6, 6, 7, 8, 8, 8, 7, 7, 6},	/* 1994 */
    {4, 6, 5, 6, 6, 7, 8, 8, 9, 8, 7, 6},	/* 1995 */
    {4, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 1996 */
    {5, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 1997 */
    {4, 6, 5, 6, 6, 7, 8, 8, 8, 7, 7, 6},	/* 1998 */
    {4, 6, 5, 6, 6, 7, 8, 8, 9, 8, 7, 6},	/* 1999 */
    {4, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2000 */
    {4, 5, 5, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2001 */
    {4, 6, 5, 6, 6, 7, 8, 8, 8, 7, 7, 6},	/* 2002 */
    {4, 6, 5, 6, 6, 7, 8, 8, 9, 8, 7, 6},	/* 2003 */
    {4, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2004 */
    {4, 5, 5, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2005 */
    {4, 6, 5, 5, 6, 7, 7, 8, 8, 7, 7, 6},	/* 2006 */
    {4, 6, 5, 6, 6, 7, 8, 8, 9, 8, 7, 6},	/* 2007 */
    {4, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2008 */
    {4, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2009 */
    {4, 6, 5, 5, 6, 7, 7, 8, 8, 7, 7, 6},	/* 2010 */
    {4, 6, 5, 6, 6, 7, 8, 8, 8, 8, 7, 6},	/* 2011 */
    {4, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2012 */
    {4, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2013 */
    {4, 6, 5, 5, 6, 7, 7, 8, 8, 7, 7, 6},	/* 2014 */
    {4, 6, 5, 6, 6, 7, 8, 8, 8, 8, 7, 6},	/* 2015 */
    {4, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2016 */
    {3, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2017 */
    {4, 5, 5, 5, 6, 7, 7, 8, 8, 7, 7, 5},	/* 2018 */
    {4, 6, 5, 6, 6, 7, 8, 8, 8, 8, 7, 6},	/* 2019 */
    {4, 5, 4, 5, 5, 6, 7, 7, 8, 7, 7, 5},	/* 2020 */
    {3, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2021 */
    {4, 5, 5, 5, 6, 7, 7, 7, 8, 7, 7, 5},	/* 2022 */
    {4, 6, 5, 6, 6, 7, 8, 8, 8, 8, 7, 6},	/* 2023 */
    {4, 5, 4, 5, 5, 6, 7, 7, 8, 7, 6, 5},	/* 2024 */
    {3, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2025 */
    {4, 5, 5, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2026 */
    {4, 6, 5, 6, 6, 7, 8, 8, 8, 7, 7, 6},	/* 2027 */
    {4, 5, 4, 5, 5, 6, 7, 7, 8, 7, 6, 5},	/* 2028 */
    {3, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2029 */
    {4, 5, 5, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2030 */
    {4, 6, 5, 6, 6, 7, 8, 8, 8, 7, 7, 6},	/* 2031 */
    {4, 5, 4, 5, 5, 6, 7, 7, 8, 7, 6, 5},	/* 2032 */
    {3, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2033 */
    {4, 5, 5, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2034 */
    {4, 6, 5, 5, 6, 7, 7, 8, 8, 7, 7, 6},	/* 2035 */
    {4, 5, 4, 5, 5, 6, 7, 7, 8, 7, 6, 5},	/* 2036 */
    {3, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2037 */
    {4, 5, 5, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2038 */
    {4, 6, 5, 5, 6, 7, 7, 8, 8, 7, 7, 6},	/* 2039 */
    {4, 5, 4, 5, 5, 6, 7, 7, 8, 7, 6, 5},	/* 2040 */
    {3, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2041 */
    {4, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2042 */
    {4, 6, 5, 5, 6, 7, 7, 8, 8, 7, 7, 6},	/* 2043 */
    {4, 5, 4, 5, 5, 6, 7, 7, 7, 7, 6, 5},	/* 2044 */
    {3, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2045 */
    {4, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2046 */
    {4, 6, 5, 5, 6, 7, 7, 8, 8, 7, 7, 6},	/* 2047 */
    {4, 5, 4, 5, 5, 6, 7, 7, 7, 7, 6, 5},	/* 2048 */
    {3, 5, 4, 5, 5, 6, 7, 7, 8, 7, 7, 5},	/* 2049 */
    {3, 5, 4, 5, 6, 7, 7, 7, 8, 7, 7, 5},	/* 2050 */
    {4, 5, 5, 5, 6, 7, 7, 7, 8, 7, 7, 5},	/* 2051 */
    {4, 5, 4, 5, 5, 6, 7, 7, 7, 7, 6, 5},	/* 2052 */
    {3, 5, 4, 5, 5, 6, 7, 7, 8, 7, 7, 5},	/* 2053 */
    {3, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2054 */
    {4, 5, 5, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2055 */
    {4, 5, 4, 5, 5, 6, 7, 7, 7, 7, 6, 5},	/* 2056 */
    {3, 5, 4, 5, 5, 6, 7, 7, 8, 7, 6, 5},	/* 2057 */
    {3, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2058 */
    {4, 5, 5, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2059 */
    {4, 5, 4, 5, 5, 6, 7, 7, 7, 6, 6, 5},	/* 2060 */
    {3, 5, 4, 5, 5, 6, 7, 7, 8, 7, 6, 5},	/* 2061 */
    {3, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2062 */
    {4, 5, 5, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2063 */
    {4, 5, 4, 5, 5, 6, 7, 7, 7, 6, 6, 5},	/* 2064 */
    {3, 5, 4, 5, 5, 6, 7, 7, 8, 7, 6, 5},	/* 2065 */
    {3, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2066 */
    {4, 5, 5, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2067 */
    {4, 5, 4, 4, 5, 6, 6, 7, 7, 6, 6, 5},	/* 2068 */
    {3, 5, 4, 5, 5, 6, 7, 7, 8, 7, 6, 5},	/* 2069 */
    {3, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2070 */
    {4, 5, 5, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2071 */
    {4, 5, 4, 4, 5, 6, 6, 7, 7, 6, 6, 5},	/* 2072 */
    {3, 5, 4, 5, 5, 6, 7, 7, 7, 7, 6, 5},	/* 2073 */
    {3, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2074 */
    {4, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2075 */
    {4, 5, 4, 4, 5, 6, 6, 7, 7, 6, 6, 5},	/* 2076 */
    {3, 5, 4, 5, 5, 6, 7, 7, 7, 7, 6, 5},	/* 2077 */
    {3, 5, 4, 5, 5, 6, 7, 7, 8, 7, 7, 5},	/* 2078 */
    {4, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2079 */
    {4, 5, 4, 4, 5, 6, 6, 7, 7, 6, 6, 5},	/* 2080 */
    {3, 5, 4, 5, 5, 6, 7, 7, 7, 7, 6, 5},	/* 2081 */
    {3, 5, 4, 5, 5, 6, 7, 7, 8, 7, 7, 5},	/* 2082 */
    {3, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2083 */
    {4, 4, 4, 4, 5, 6, 6, 6, 7, 6, 6, 4},	/* 2084 */
    {3, 5, 4, 5, 5, 6, 7, 7, 7, 7, 6, 5},	/* 2085 */
    {3, 5, 4, 5, 5, 6, 7, 7, 8, 7, 7, 5},	/* 2086 */
    {3, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2087 */
    {4, 4, 4, 4, 4, 6, 6, 6, 7, 6, 6, 4},	/* 2088 */
    {3, 5, 4, 5, 5, 6, 7, 7, 7, 7, 6, 5},	/* 2089 */
    {3, 5, 4, 5, 5, 6, 7, 7, 8, 7, 6, 5},	/* 2090 */
    {3, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2091 */
    {4, 4, 4, 4, 4, 6, 6, 6, 7, 6, 6, 4},	/* 2092 */
    {3, 5, 4, 5, 5, 6, 7, 7, 7, 6, 6, 5},	/* 2093 */
    {3, 5, 4, 5, 5, 6, 7, 7, 8, 7, 6, 5},	/* 2094 */
    {3, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2095 */
    {4, 4, 4, 4, 4, 6, 6, 6, 7, 6, 6, 4},	/* 2096 */
    {3, 5, 4, 5, 5, 6, 6, 7, 7, 6, 6, 5},	/* 2097 */
    {3, 5, 4, 5, 5, 6, 7, 7, 8, 7, 6, 5},	/* 2098 */
    {3, 5, 4, 5, 5, 7, 7, 7, 8, 7, 7, 5},	/* 2099 */
    {4, 5, 5, 5, 5, 7, 7, 7, 8, 7, 7, 6} 	/* 2100 */
};

static gshort statutory_holidays[] = {
    0x2601, 0x2621, 0x2622, 0x2623, 0x2624, 0x2625, 0x2626, 0x2627, 0x265f,
    0x2676, 0x2679, 0x267a, 0x267b, 0x267d, 0x269e, 0x2700, 0x2710, 0x2712,
    0x2713, 0x2714, 0x2715, 0x2718,  /* 2019 */
    0x2801, 0x2813, 0x2818, 0x281b, 0x281c, 0x281d, 0x281e, 0x2820, 0x2861,
    0x2875, 0x287a, 0x287d, 0x287e, 0x2882, 0x28b1, 0x28b2, 0x28b4, 0x290f,
    0x2913, 0x2914, 0x2917, 0x2918, 0x2919, 0x291a, 0x291c,  /* 2020 */
    0x2a01, 0x2a26, 0x2a2a, 0x2a2b, 0x2a2e, 0x2a2f, 0x2a30, 0x2a33, 0x2a5f,
    0x2a73, 0x2a7b, 0x2a7c, 0x2a7d, 0x2a80, 0x2aa5, 0x2b05, 0x2b07, 0x2b08,
    0x2b0d, 0x2b12, 0x2b15, 0x2b16, 0x2b17, 0x2b18, 0x2b1a,  /* 2021 */
    0x2c03, 0x2c1d, 0x2c1e, 0x2c1f, 0x2c20, 0x2c21, 0x2c22, 0x2c23, 0x2c5c,
    0x2c5e, 0x2c5f, 0x2c72, 0x2c78, 0x2c7a, 0x2c7b, 0x2c7c, 0x2c7f, 0x2c9a,
    0x2cff, 0x2d14, 0x2d15, 0x2d16, 0x2d17, 0x2d18, 0x2d19, 0x2d1a  /* 2022 */
}

static int days_in_lunar_month[2]  = {29,30};

static	char	*gan_list[] = {
    /*
     * 十天干: "Jiǎ" "Yǐ" "Bǐng" "Dīng" "Wù" "Jǐ" "Gēng" "Xīn" "Rén" "Guǐ"
     */
    N_("Ji\307\216"), N_("Y\307\220"),   N_("B\307\220ng"), N_("D\304\253ng"), N_("W\303\271"),
    N_("J\307\220"),  N_("G\304\223ng"), N_("X\304\253n"),  N_("R\303\251n"),  N_("Gu\307\220")
};

static	char	*zhi_list[] = {
    /*
     * 十二地支: "Zǐ" "Chǒu" "Yín" "Mǎo" "Chén" "Sì" "Wǔ" "Wèi" "Shēn" "Yǒu" "Xū" "Hài" */
    N_("Z\307\220"),  N_("Ch\307\222u"), N_("Y\303\255n"),  N_("M\307\216o"),  N_("Ch\303\251n"), N_("S\303\254"),
    N_("W\307\224"),  N_("W\303\250i"),  N_("Sh\304\223n"), N_("Y\307\222u"),  N_("X\305\253"),   N_("H\303\240i")
};

static	char   *shengxiao_list[] = {
    N_("Mouse"), N_("Ox"), N_("Tiger"), N_("Rabbit"), N_("Dragon"), N_("Snake"),
    N_("Horse"), N_("Goat"), N_("Monkey"), N_("Rooster"), N_("Dog"), N_("Pig")
};
static	char   *lunar_month_list[] = {
    N_("Jan"), N_("Feb"), N_("Mar"), N_("Apr"), N_("May"), N_("Jun"),
    N_("Jul"), N_("Aug"), N_("Sep"), N_("Oct"), N_("Nov"), N_("Dec")
};
static	char   *lunar_day_list[] = {
    /*
     * 从 "初一" 到 "三十"
     * "Chūyī" "Chūèr" "Chūsān" "Chūsì" "Chūwǔ" "Chūliù" "Chūqī" "Chūbā" "Chūjiǔ" "Chūshí"
     * "Shíyī" "Shíèr" "Shísān" "Shísì" "Shíwǔ" "Shíliù" "Shíqī" "Shíbā" "Shíjiǔ" "Èrshí"
     * "Èryī" "Èrèr" "Èrsān" "Èrsì" "Èrwǔ" "Èrliù" "Èrqī" "Èrbā" "Èrjiǔ" "Sānshí"
     */

    N_("Ch\305\253y\304\253"), N_("Ch\305\253\303\250r"), N_("Ch\305\253s\304\201n"), N_("Ch\305\253s\303\254"), N_("Ch\305\253w\307\224"),
    N_("Ch\305\253li\303\271"), N_("Ch\305\253q\304\253"), N_("Ch\305\253b\304\201"), N_("Ch\305\253ji\307\224"), N_("Ch\305\253sh\303\255"),
    N_("Sh\303\255y\304\253"), N_("Sh\303\255\303\250r"), N_("Sh\303\255s\304\201n"), N_("Sh\303\255s\303\254"), N_("Sh\303\255w\307\224"),
    N_("Sh\303\255li\303\271"), N_("Sh\303\255q\304\253"), N_("Sh\303\255b\304\201"), N_("Sh\303\255ji\307\224"), N_("\303\210rsh\303\255"),
    N_("\303\210ry\304\253"), N_("\303\210r\303\250r"), N_("\303\210rs\304\201n"), N_("\303\210rs\303\254"), N_("\303\210rw\307\224"),
    N_("\303\210rli\303\271"), N_("\303\210rq\304\253"), N_("\303\210rb\304\201"), N_("\303\210rji\307\224"), N_("S\304\201nsh\303\255")
};

static gchar *twelve_constellations[] = {
    N_("Capricornus"), N_("Aquarius"), N_("Pisces"), N_("Aries"), N_("Taurus"),
    N_("Gemini"), N_("Cancer"), N_("Leo"), N_("Virgo"), N_("Libra"),
    N_("Scorpius"), N_("Sagittarius")
};

static int days_of_constellations[]  = {
    20, 50, 80, 110, 141, 172, 204,
    235, 266, 296, 326, 356, 366
};

static CLDate first_solar_date  = {1900, 1, 31, 0, FALSE }; /* 1900年1月31日 */
static CLDate first_lunar_date  = {1900, 1, 1, 0, FALSE };  /* 1900年元月初一 */
static CLDate first_gan_date    = {6, 4, 0, 0, FALSE };     /* 庚年午月甲日甲时 */
static CLDate first_zhi_date    = {0, 2, 4, 0, FALSE};      /* 子年寅月辰日子时 */

G_END_DECLS

#endif /* __LUNAR_DATE_PRIVATE_H__ */

/*
   vi:ts=4:wrap:ai:
   */
