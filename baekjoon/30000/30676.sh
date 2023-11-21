read x
if [ $x -ge 620 ]; then
	echo Red
elif [ $x -ge 590 ]; then
	echo Orange
elif [ $x -ge 570 ]; then
	echo Yellow
elif [ $x -ge 495 ]; then
	echo Green
elif [ $x -ge 450 ]; then
	echo Blue
elif [ $x -ge 425 ]; then
	echo Indigo
else
	echo Violet
fi
