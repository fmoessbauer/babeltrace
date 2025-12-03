#!/bin/bash
#
# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2025 Siemens
#

# This file tests if an LTTng index is created if
# create-lttng-index=true parameter is set. Both streams
# with and without packages are tested.

SH_TAP=1

if [ -n "${BT_TESTS_SRCDIR:-}" ]; then
	UTILSSH="$BT_TESTS_SRCDIR/utils/utils.sh"
else
	UTILSSH="$(dirname "$0")/../../utils/utils.sh"
fi

# shellcheck source=../../utils/utils.sh
source "$UTILSSH"

# Directory containing the Python test source.
data_dir="$BT_TESTS_DATADIR/plugins/sink.ctf.fs/create-lttng-index"

temp_stdout=$(mktemp)
temp_expected_stdout=$(mktemp)
temp_stderr=$(mktemp)
temp_output_dir=$(mktemp -d)
trace_dir="$temp_output_dir/trace"

if [ "$BT_TESTS_ENABLE_PYTHON_PLUGINS" != "1" ]; then
	plan_skip_all "This test requires the Python plugin provider"
	exit
fi

plan_tests 17

bt_cli --stdout-file "$temp_stdout" --stderr-file "$temp_stderr" -- \
	"--plugin-path=${data_dir}" \
	-c src.foo.TheSource \
		-p "with-packet-msgs=false" \
	-c sink.ctf.fs \
		-p "path=\"${temp_output_dir}\"" \
		-p 'ctf-version="1"' \
		-p "create-lttng-index=true"
ok "$?" "run babeltrace"

# Check stdout.
if [ "$BT_TESTS_OS_TYPE" = "mingw" ]; then
	# shellcheck disable=SC2028
	echo "Created CTF trace \`$(cygpath -m "${temp_output_dir}")\\trace\`." > "$temp_expected_stdout"
else
	echo "Created CTF trace \`${trace_dir}\`." > "$temp_expected_stdout"
fi

bt_diff "$temp_expected_stdout" "$temp_stdout"
ok "$?" "expected message on stdout"

# Check stderr.
bt_diff "/dev/null" "$temp_stderr"
ok "$?" "stderr is empty"

# Verify only the expected files exist.
files=("$trace_dir"/*)
num_files=${#files[@]}
is "$num_files" "3" "expected number of files in output directory"

test -f "$trace_dir/metadata"
ok "$?" "metadata file exists"

test -f "$trace_dir/the-stream"
ok "$?" "the-stream file exists"

test -f "$trace_dir/index/the-stream.idx"
ok "$?" "index/the-stream.idx file exists"

# Read back the output trace to ensure the index can be parsed
cat <<- 'END' > "$temp_expected_stdout"
the-event: 
the-event: 
the-event: 
END
bt_test_cli "read back output trace" --expect-stdout "$temp_expected_stdout" -- \
	"$trace_dir"

# Run same test, but with packages. Index must be bigger
bt_cli -- \
	"--plugin-path=${data_dir}" \
	-c src.foo.TheSource \
		-p "with-packet-msgs=true" \
	-c sink.ctf.fs \
		-p "path=\"${temp_output_dir}\"" \
		-p 'ctf-version="1"' \
		-p "create-lttng-index=true"
ok "$?" "run babeltrace"

test -f "${trace_dir}-0/index/the-stream.idx"
ok "$?" "index/the-stream.idx file exists"

# Verify the index with packages is larger than the one without packages
size_original=$(stat -c%s "${trace_dir}/index/the-stream.idx")
size_packages=$(stat -c%s "${trace_dir}-0/index/the-stream.idx")
test "$size_packages" -gt "$size_original"
ok "$?" "index with packages is larger than without packages"

# Ensure the package.context cpu_id field is not escaped, as needed
# as-is by trace-compass
grep -q ' cpu_id;' "${trace_dir}-0/metadata"
ok "$?" "package.context cpu_id is not escaped"

# Read back the output trace to ensure the index can be parsed
cat <<- 'END' > "$temp_expected_stdout"
the-event: { cpu_id = 0 }
the-event: { cpu_id = 0 }
the-event: { cpu_id = 0 }
END
bt_test_cli "read back output trace-0" --expect-stdout "$temp_expected_stdout" -- \
	"${trace_dir}-0"

rm -f "$temp_stdout"
rm -f "$temp_stderr"
rm -f "$temp_expected_stdout"
for t in "${trace_dir}" "${trace_dir}-0"; do
	rm -f "$t/metadata"
	rm -f "$t/the-stream"
	rm -f "$t/index/the-stream.idx"
	rmdir "$t/index"
	rmdir "$t"
done
rmdir "$temp_output_dir"
