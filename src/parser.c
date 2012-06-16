/*
 * parser.c - IEC messages parsing utilities
 *
 * Copyright (C) 2012 I. S. Gorbunov <igor.genius at gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iecparser.h>
#include <errno.h>

int IecParseMessage(char *buffer, size_t maxsize, size_t msgsize,
	void *msg, enum naviSentence_t *msgtype)
{
	return -ENOSYS;
}

//
// Алгоритм разбора:
// 1. Установить границы сообщения (от знака $ до <cr><lf>)
// 2. Подсчитать контрольную сумму и убедиться, что сообщение получено верно
// 3. Выяснить Talker ID и тип сообщения
// 4. С помощью соответствующего метода осуществить разбор полей сообщения

