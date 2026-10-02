outfile: main.o clearinputbuffer.o addnewbook.o checkbookexits.o updatebook.o updatebyid.o updatebyname.o removebook.o removebyid.o removebyname.o searchbybook.o searchbyid.o searchbyname.o searchbyauthor.o viewall.o issue.o save.o
	cc main.c clearinputbuffer.c addnewbook.c checkbookexits.c updatebook.c updatebyid.c updatebyname.c removebook.c removebyid.c removebyname.c searchbybook.c searchbyid.c searchbyname.c searchbyauthor.c viewall.c issue.c save.c -o library
main.o:main.c
	cc -c main.c
clearinputbuffer.o:clearinputbuffer.c
	cc -c clearinputbuffer.c
addnewbook.o:addnewbook.c
	cc -c addnewbook.c
checkbookexits.o:checkbookexits.c
	cc -c checkbookexits.c
updatebook.o:updatebook.c
	cc -c updatebook.c
updatebyid.o:updatebyid.c
	cc -c updatebyid.c
updatebyname.o:updatebyname.c
	cc -c updatebyname.c
removebook.o:removebook.c
	cc -c removebook.c
removebyid.o:removebyid.c
	cc -c removebyid.c 
removebyname.o:removebyname.c
	cc -c removebyname.c
searchbybook.o:searchbybook.c
	cc -c searchbybook.c
searchbyid.o:searchbyid.c
	cc -c searchbyid.c
searchbyname.o:searchbyname.c
	cc -c searchbyname.c
searchbyauthor.o:searchbyauthor.c
	cc -c searchbyauthor.c
viewall.o:viewall.c
	cc -c viewall.c
issue.o:issue.c
	cc -c issue.c
save.o :save.c
	cc -c save.c

