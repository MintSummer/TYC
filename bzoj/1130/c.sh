for i in {1..44} 
do
	mv "$i.in" 1130.in
	mv "$i.out" ans.out
	./1130 < 1130.in > 1130.out
	./spj
	if [[ $? == 1 ]] ; then
		exit
	fi
	mv 1130.in "$i.in"
	mv ans.out "$i.out"
done
