while true ; do
	./rand > rand.in
	./2741 < rand.in > tyc.out
	./ans < rand.in > ans.out
	if diff tyc.out ans.out ; then
		printf "AC\n"
	else
		printf "WA\n"
		exit
	fi
done
