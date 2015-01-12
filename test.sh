for filename in tests/*.c; do
	echo "Compile $filename"
	./gazl $filename
done
