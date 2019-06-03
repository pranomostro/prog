#!/bin/sh

while true; do
	echo '----------------------------------------------------------------------' 1>&2

	tmpdir=$(mktemp -d '/tmp/test.XXXXXX')

	echo "${tmpdir}" 1>&2

	mkfifo "${tmpdir}"/in.1 "${tmpdir}"/in.2 "${tmpdir}"/in.3 "${tmpdir}"/emit.1 "${tmpdir}"/emit.2 "${tmpdir}"/emit.3

	for i in $(seq 1 3); do
		if ! test -e "${tmpdir}"/in.$i && -e "${tmpdir}"/emit.$i; then
			echo 'treat test: did not find '$i' in "${tmpdir}".' 1>&2
			exit 3
		fi
	done

	ls "${tmpdir}" 1>&2

	echo 'setting up middlemen' 1>&2

	cat <"${tmpdir}"/in.1 >"${tmpdir}"/emit.1 &
	cat <"${tmpdir}"/in.2 >"${tmpdir}"/emit.2 &
	cat <"${tmpdir}"/in.3 >"${tmpdir}"/emit.3 &

	echo 'setting up emitters' 1>&2

	cat "${tmpdir}"/emit.1 1>&2 &
	cat "${tmpdir}"/emit.2 1>&2 &
	cat "${tmpdir}"/emit.3 1>&2 &

	echo 'setting up input' 1>&2

	echo a >"${tmpdir}"/in.1
	echo b >"${tmpdir}"/in.2
	echo c >"${tmpdir}"/in.3

	wait

	rm -r "${tmpdir}"
done
