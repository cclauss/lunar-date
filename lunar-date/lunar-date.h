/* vi: set sw=4 ts=4: */
/*
 * lunar-date.h
 *
 * This file is part of liblunar.
 *
 * Copyright (C) 2007-2011 yetist <yetist@gmail.com>.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA.
 * */

#ifndef __LUNAR_DATE_H__
#define __LUNAR_DATE_H__  1

#include	<glib-object.h>

G_BEGIN_DECLS


#define LUNAR_TYPE_DATE				 (lunar_date_get_type ())
#define LUNAR_DATE_ERROR	(lunar_date_error_quark ())

G_DECLARE_FINAL_TYPE (LunarDate, lunar_date, LUNAR, DATE, GObject)

//typedef guint8	GDateHour;


/**
 * LunarDateError:
 * @LUNAR_DATE_ERROR_INTERNAL: internal error.
 * @LUNAR_DATE_ERROR_YEAR: year setup error.
 * @LUNAR_DATE_ERROR_MONTH: month setup error.
 * @LUNAR_DATE_ERROR_DAY: day setup error.
 * @LUNAR_DATE_ERROR_HOUR: hour setup error.
 * @LUNAR_DATE_ERROR_LEAP: isleap setup error.
 */
typedef enum
{
	LUNAR_DATE_ERROR_INTERNAL,
	LUNAR_DATE_ERROR_YEAR,
	LUNAR_DATE_ERROR_MONTH,
	LUNAR_DATE_ERROR_DAY,
	LUNAR_DATE_ERROR_HOUR,
	LUNAR_DATE_ERROR_LEAP
} LunarDateError;

GQuark lunar_date_error_quark (void);

LunarDate*	lunar_date_new				 (void);
void		lunar_date_set_solar_date	  (LunarDate *date,
											GDateYear year,
											GDateMonth month,
											GDateDay day,
											guint8 hour,
											GError	**error);
void		lunar_date_set_lunar_date	  (LunarDate *date,
											GDateYear year,
											GDateMonth month, 
											GDateDay day,
											guint8 hour,
											gboolean isleap,
											GError **error);
gchar*		lunar_date_get_jieri		  (LunarDate *date, const gchar *delimiter);
gchar*		lunar_date_add_solar_jieri	  (LunarDate *date, GDateMonth month, GDateDay day, const gchar *holiday);
gchar*		lunar_date_add_lunar_jieri	  (LunarDate *date, GDateMonth month, GDateDay day, const gchar *holiday);
gchar*		lunar_date_add_week_jieri	  (LunarDate *date, GDateMonth month, gint week, gint which, const gchar *holiday);
gchar*		lunar_date_strftime			  (LunarDate *date, const char *format);
void		lunar_date_free				  (LunarDate *date);

G_END_DECLS

#endif /*__LUNAR_DATE_H__ */
