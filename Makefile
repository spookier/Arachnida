CC = python3
PROGRAM = spider.py
LINK = https://store.steampowered.com

all:
	${CC} ${PROGRAM} ${LINK}

r:
	${CC} ${PROGRAM} -r ${LINK}



fclean:
	rm -rf data
	rm -rf __pycache__

.PHONY: all clean
