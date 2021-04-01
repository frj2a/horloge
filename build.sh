#! /bin/bash
if [ -e Makefile ]
then
	make distclean -s && \
	rm -fR GeneratedFiles release debug *.qm
fi
QT_OTIMIZA="linux-g++"
MAQUINA=`uname -m`
if [ "$MAQUINA" = "x86_64" ]
then
	QT_OTIMIZA="linux-g++-64"
fi
echo -e - - -Compilando o programa '\033[1;33m'Horloge'\033[0m', um relógio transparente até para eventos, para a plataforma '\033[1;33m'$MAQUINA'\033[0m' ...

lrelease -qt=qt5 horloge.pro 1> /dev/null 2> /dev/null

VER="PROJECT_NUMBER         = "`qmake -r -spec $QT_OTIMIZA "CONFIG-=debug_and_release release debug" "CONFIG+=release" 2>&1 | grep "Project MESSAGE:" | cut -d\  -f5`
PROJECT_NUMBER=`echo $VER | sed -e s/\ /\\\\\\\\\ /g -e  s-/-\\\\\\\/-g`
qmake -r -spec $QT_OTIMIZA "CONFIG-=debug_and_release release debug" "CONFIG+=release" 1> /dev/null 2> /dev/null
cat Doxyfile.linux | sed s/"PROJECT_NUMBER[\ ]*=\ "/"$PROJECT_NUMBER"/ > Doxyfile && /usr/bin/make qmake_all 1> /dev/null 2> /dev/null

/usr/bin/make $MAKEOPTS -s && \
strip -s horloge

rm -fR GeneratedFiles debug *.qm .qmake.stash
if [ -e /usr/bin/doxygen ]
then
	echo -e '\033[1;35m'Rodando doxygen em segundo plano.'\033[0m'
	{ \
	doxygen Doxyfile 2> /dev/null 1> /dev/null ; \
	if [ -d latex ] ; then \
		cd latex ; \
		make -s 2> /dev/null 1> /dev/null ; \
		mv refman.pdf .. ; \
		cd .. ; \
		rm -fR latex ; \
	fi ; \
	rm -f Doxyfile ; \
	echo -e '\033[1;35m'doxygen finalizado.\\n\\n'\033[0m'
	} &
fi
if [ -e /usr/bin/cloc ]
then
	cloc *.cpp *.h
fi
echo -e - - -Finalizada a compilação do programa '\033[1;33m'Horloge'\033[0m', um relógio transparente até para eventos, para a plataforma '\033[1;33m'$MAQUINA'\033[0m' ...
