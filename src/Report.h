/*
 * Report.h
 *
 *  Created on: 9 Mar 2014
 *      Author: homac
 */

#ifndef REPORT_H_
#define REPORT_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

class Report {
public:
	static void sysfatal(const char* format, ...) {
		va_list ap;
		fprintf(stderr, "fatal: ");
		va_start(ap, format);
		vfprintf(stderr, format, ap);
		va_end(ap);
		perror("  system error message");
		abort();
	}
	static void fatal(const char* format, ...) {
		va_list ap;
		fprintf(stderr, "fatal: ");
		va_start(ap, format);
		vfprintf(stderr, format, ap);
		va_end(ap);

		fprintf(stderr, "\nabort!");
		abort();
	}
	static void info(const char* format, ...) {
		va_list ap;
		fprintf(stdout, "info: ");
		va_start(ap, format);
		vfprintf(stdout, format, ap);
		va_end(ap);

		fflush(stdout);
	}
};

#endif /* REPORT_H_ */
