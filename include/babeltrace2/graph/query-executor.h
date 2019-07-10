#ifndef BABELTRACE2_GRAPH_QUERY_EXECUTOR_H
#define BABELTRACE2_GRAPH_QUERY_EXECUTOR_H

/*
 * Copyright 2017-2018 Philippe Proulx <pproulx@efficios.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __BT_IN_BABELTRACE_H
# error "Please include <babeltrace2/babeltrace.h> instead."
#endif

#include <babeltrace2/types.h>
#include <babeltrace2/logging.h>

#ifdef __cplusplus
extern "C" {
#endif

extern
bt_query_executor *bt_query_executor_create(void);

typedef enum bt_query_executor_query_status {
	BT_QUERY_EXECUTOR_QUERY_STATUS_OK		= __BT_FUNC_STATUS_OK,
	BT_QUERY_EXECUTOR_QUERY_STATUS_AGAIN		= __BT_FUNC_STATUS_AGAIN,
	BT_QUERY_EXECUTOR_QUERY_STATUS_UNSUPPORTED	= __BT_FUNC_STATUS_UNSUPPORTED,
	BT_QUERY_EXECUTOR_QUERY_STATUS_CANCELED		= __BT_FUNC_STATUS_CANCELED,
	BT_QUERY_EXECUTOR_QUERY_STATUS_ERROR		= __BT_FUNC_STATUS_ERROR,
	BT_QUERY_EXECUTOR_QUERY_STATUS_MEMORY_ERROR	= __BT_FUNC_STATUS_MEMORY_ERROR,
	BT_QUERY_EXECUTOR_QUERY_STATUS_INVALID_OBJECT	= __BT_FUNC_STATUS_INVALID_OBJECT,
	BT_QUERY_EXECUTOR_QUERY_STATUS_INVALID_PARAMS	= __BT_FUNC_STATUS_INVALID_PARAMS,
} bt_query_executor_query_status;

extern
bt_query_executor_query_status bt_query_executor_query(
		bt_query_executor *query_executor,
		const bt_component_class *component_class,
		const char *object, const bt_value *params,
		bt_logging_level logging_level, const bt_value **result);

typedef enum bt_query_executor_cancel_status {
	BT_QUERY_EXECUTOR_CANCEL_STATUS_OK	= __BT_FUNC_STATUS_OK,
} bt_query_executor_cancel_status;

extern
bt_query_executor_cancel_status bt_query_executor_cancel(
		bt_query_executor *query_executor);

#ifdef __cplusplus
}
#endif

#endif /* BABELTRACE2_GRAPH_QUERY_EXECUTOR_H */
