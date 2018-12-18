while true ; do
	./rand > rand.in 
	./30E < rand.in > tyc.out
	./ans < rand.in > ans.out
	if diff ans.out tyc.out ; then
		printf "AC\n"
	else
		printf "WA\n"
		exit
	fi
done
