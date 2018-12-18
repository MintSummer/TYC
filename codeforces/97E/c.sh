while true ; do
	./rand > rand.in 
	./97E < rand.in > tyc.out 
	./ans < rand.in > ans.out
	if diff tyc.out ans.out ; then
		echo AC
	else
		echo WA
	fi
done
