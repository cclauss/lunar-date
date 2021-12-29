#! /usr/bin/env python
# -*- encoding:utf-8 -*-
# FileName: table2code.py

"This file is part of lunar-date"

__author__   = "yetist"
__copyright__= "Copyright (C) 2019-2021 yetist <yetist@yetibook>"
__license__  = """
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this library; if not, see <http://www.gnu.org/licenses/>.
"""

import toml

class Table(object):
    def __init__ (self, file):
        self.file = file
        self.data = None

    def load(self):
        fp = open(self.file)
        self.data = toml.load(fp)
        self.lst = list(self.data.keys())
        self.lst.sort()
        self.start = self.lst[0]
        self.end = self.lst[-1]
        self.count = len(self.lst)

    def get_year_info(self, year):
        year_data = self.data[year]
        info = 0
        if year_data['leap_days'] == 30:
            info += 1
        for i in year_data['days']:
            info = info << 1
            if i == 30:
                info |= 1
            else:
                info |= 0
        info = info << 4
        info += year_data['leap']
        #print(bin(info), info, hex(info))
        return hex(info)

    def get_fest(self, year):
        year_data = self.data[year]
        return year_data['jie']

    def gen_year_info(self):
        header="""
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
"""
        print(header)
        for i in self.lst:
            val = self.get_year_info(i)
            if int(i) % 5 == 0:
                print("{}  /* {} */".format(val, i), end = '\n')
            elif int(i) % 5 == 1:
                print("        {},".format(val), end = ' ')
            elif int(i) % 5 == 4:
                print("{} ".format(val), end = ' ')
            else:
                print("{},".format(val), end = ' ')
        print("  /* {} */".format(i), end = '\n};\n\n')

    def gen_fest(self):
        print("static gchar fest[NUM_OF_YEARS][%d] = {" % self.count)
        for i in self.lst:
            print("{", end = ' ')
            #jie_lst = [ str(x) for x in self.get_holidays(i)]
            #x = ', '.join(jie_lst)
            #print(x, end = ' ')
            #print("},   /* %s */" % str(i))
        print('};\n\n')

    """
    算法：
    使用一个整数表示当年上班和休息日

    法定节假日算法：
    使用一个 uint16 类型表示当年的法定假日调整情况

    年份 [15:9], 共7位，值加上2000表示公历年份。 (1<<7) - 1 = 127，最大可表示年份为 2127 年。
    日期 [8:0], 共9位，值以二进制位来表示当年哪天的上班/休息状态需要调整(即休息变上班，上班变休息)，(1<<9) - 1 = 511位，可表示一年 365 天的状态。

    """
    def get_holidays(self, year):
        year_data = self.data[year]
        return year_data.get('statutory_holidays')
#       print(dir(year_data))
#        print(year_data.keys())
#        if year_data.has_keys('statutory_holidays'):
#            return year_data['statutory_holidays']
#        else:
#            return []

    def gen_holidays(self):
        print("static gchar statutory_holidays[NUM_OF_YEARS][%d] = {" % self.count)
        for i in self.lst:
            days = self.get_holidays(i)
            if days:
                year = int(i) - 2000
                #year = year << 9
                print (year, hex(year << 9))
                print (i)
                for j in days:
                    print(j)
            #print("{", end = ' ')
            #jie_lst = [ str(x) for x in self.get_holidays(i)]
            #print(jie_lst)
        print("  /* {} */".format(i), end = '\n};\n\n')

if __name__=="__main__":
    t = Table("table.toml")
    t.load()
    #t.gen_year_info()
    #t.gen_fest()
    t.gen_holidays()
