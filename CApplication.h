// "$Date: 2019-11-22 19:44:01 -0300 (sex, 22 nov 2019) $"
// "$Author: chico $"
// "$Revision: 159 $"

#ifndef CAPPLICATION_H
#define CAPPLICATION_H

#include "horloge.h"
#include <QApplication>
#include <QSessionManager>
#include <QHash>
#include <QStringList>
#include <QDir>
#include <QFileInfo>
#include <QTranslator>
#include <QSharedMemory>

//! \class CApplication CApplication.h
//! \brief Derivada da __QApplication__; implementa as funcionalidades de tradução e de sinalização de encerramento do programa.
class CApplication : public QApplication	{
	Q_OBJECT

public:

	//! \brief Construtora, que simplesmente repassa os argumentos para a classe pai.
	//! \param argc Tradicional contagem de parâmetros na linha de comando, incluindo a própria chamada do programa;
	//! \param argv Tradicional ponteiro para todos os parâmetros da linha de comando;
	CApplication(int &argc , char **argv);	// note a forma de acesso ao "argc" por referência (e não por cópia); ver documentação!

	//! \brief Para compatibilidade com a inicialização padrão no arquivo "main.c"
	//! \param sessao Objeto principal do programa.
	void setSession(QWidget * session);

	//! \brief Carrega as traduções para o conjunto de idiomas especificado no parâmetro fornecido.
	//! \param dir Nome do diretório, em formato de texto, onde se encontram as traduções individuais.
	static void loadTranslations(const QString& dir);

	//! \brief Carrega as traduções para o conjunto de idiomas especificado no parâmetro fornecido.
	//! \param dir Diretório onde se encontram as traduções individuais.
	static void loadTranslations(const QDir& dir);

	//! \brief Devolve a lista de traduções disponíveis.
	//! \returns Lista dos nomes de código das localizações (traduções) disponíveis.
	static const QStringList availableLanguages();

	//! \brief Provoca a consolidação final da base de dados.
	//! \param manager Gerenciador de Sessão do gerenciador de janelas do ambiente gráfico usado.
	void commitData( QSessionManager &manager);

private:
	QWidget * mSession;									//!< Objeto principal, que instancia os objetos de interface de usuário e com os dispositivos.
	static QTranslator* current;						//!< Objeto que contém a tradução em uso da interface de usuário.
	static QHash<QString, QTranslator*> mTranslators;	//!< Objeto que contém as traduções da interface de usuário.

public
Q_SLOTS:

	//! \brief Configura a tradução a partir do código de localização fornecido.
	//! \param locale Código de localização para a tradução solicitada.
	static void setLanguage(const QString& locale);

};

#endif // CAPPLICATION_H
