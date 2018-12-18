while true ; do
	./rand > rand.in 
	./new < rand.in > tyc.out 
	./ans < rand.in > ans.out
	if diff tyc.out ans.out ; then
		printf "AC\n"
	else 
		printf "WA\n"
		exit
	fi
done
