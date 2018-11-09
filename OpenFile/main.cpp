//#include "mainwindow.h"
//#include <QApplication>
//
//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//
//    return a.exec();
//}

//#include <QDir>
//#include <QApplication>
//#include <QDebug>
//#include <QStandardPaths>

//int main(int argc, char *argv[]) {
//
//
//	QApplication app(argc, argv);
//
//	//QDir dir(QDir::currentPath());
//	foreach(QFileInfo drive, QDir::drives())
//	{
//		qDebug() << "Drive: " << drive.absolutePath();
//		QDir dir(drive.absolutePath());
//		QStringList infolist = dir.entryList(QDir::NoDotAndDotDot | QDir::AllEntries | QDir::Readable, QDir::IgnoreCase | QDir::DirsLast);
//		for (int i = 0; i < infolist.size(); i++)
//		{
//			qDebug() << infolist.at(i);
//		}
//		qDebug() << endl;
//	}
//
//	//qDebug() << "dir start " << dir << "dir end";
//	//QStringList infolist = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
//
//
//
//	//QFileInfoList fileInfoList = dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
//	//for (auto &e : fileInfoList)
//	//{
//	//	qDebug() << e.filePath() << " " << (e.isFile() ? "File" : "Dir") << endl;
//	//}
//
//	//QString tmp;
//	//qDebug() << (tmp = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)) << endl;
//	////qDebug() << 
//
//	//QStringList l = QStandardPaths::standardLocations(QStandardPaths::DesktopLocation);
//	//QStringList movie = QStandardPaths::standardLocations(QStandardPaths::MoviesLocation);
//	//QStringList doc = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
//	//QStringList pic = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
//	//QStringList music = QStandardPaths::standardLocations(QStandardPaths::MusicLocation);
//
//	/*for (auto &e : l)
//	{
//		qDebug() << e << endl;
//	}
//	for (auto &e : movie)
//	{
//		qDebug() << e << endl;
//	}
//	for (auto &e : doc)
//	{
//		qDebug() << e << endl;
//	}
//	for (auto &e : pic)
//	{
//		qDebug() << e << endl;
//	}
//	for (auto &e : music)
//	{
//		qDebug() << e << endl;
//	}*/
//	//qDebug() << QStandardPaths::displayName(QStandardPaths::DesktopLocation) << endl;
//
//	return app.exec();
//}

//#include <QCoreApplication>
//#include <QStorageInfo>
//#include <QDebug>

//int main(int argc, char *argv[])
//{
//	QCoreApplication a(argc, argv);
//
//	QList<QStorageInfo> list = QStorageInfo::mountedVolumes();
//	qDebug() << "Volume Num: " << list.size();
//	for (QStorageInfo& si : list)
//	{
//		qDebug() << "Name: " << si.name();
//		qDebug() << "Block Size: " << si.blockSize();
//		qDebug() << "Bytes Avaliable: " << si.bytesAvailable();
//		qDebug() << "Bytes Free: " << si.bytesFree();
//		qDebug() << "Bytes Total: " << si.bytesTotal();
//		qDebug() << "Display Name: " << si.displayName();
//		qDebug() << "File System Type: " << si.fileSystemType();
//		qDebug() << "Is ReadOnly: " << si.isReadOnly();
//		qDebug() << "Is Root: " << si.isRoot();
//		qDebug() << endl;
//	}
//
//	qDebug() << QStorageInfo::root().device();
//
//	return a.exec();
//}


//#include <stdio.h>
//#include <conio.h>
//#include <tchar.h>
//#include <winerror.h>
#include <Windows.h>
#include <iostream>
#include <QObject>
#include <QStringList>
#include <QFileinfo>
#include <QDebug>
#include <QFile>
#include <QMap>
#include <QPair>

using namespace std;

#pragma comment(lib,"Ole32.lib")
#pragma comment(lib,"OleAut32.lib")

bool GetAllOfficeFilePath(QMap<QString, QStringList>& mapPaths)
{
	//CLSID clsid;
	CoInitialize(NULL);
	HRESULT hr = S_FALSE;
	IRunningObjectTable* pRot = NULL;
	IEnumMoniker* pEnumMoniker = NULL;
	IMoniker* pMoniker = NULL;
	hr = GetRunningObjectTable(0, &pRot);
	if (FAILED(hr))
	{
		cout << "GetRunningObjectTable failed" << endl;
		return false;
	}
	hr = pRot->EnumRunning(&pEnumMoniker);
	if (FAILED(hr))
	{
		cout << "EnumRunning failed" << endl;
		return false;
	}

	hr = pEnumMoniker->Reset();
	if (FAILED(hr))
	{
		cout << "Reset failed" << endl;
		return false;
	}

	IBindCtx *pbc;
	CreateBindCtx(0, &pbc);
	int index = 1;

	while ((hr = pEnumMoniker->Next(1, &pMoniker, NULL)) == S_OK)
	{
		OLECHAR* szDisplayName;
		hr = pMoniker->GetDisplayName(pbc, NULL, &szDisplayName);
		if (FAILED(hr))
		{
			cout << "GetDisplayName failed" << endl;
		}
		else
		{
			DWORD dwLen = WideCharToMultiByte(CP_ACP, 0, szDisplayName, -1, NULL, 0, NULL, FALSE);
			char* szResult = new char[dwLen];
			WideCharToMultiByte(CP_ACP, 0, szDisplayName, -1, szResult, dwLen, NULL, FALSE);
			//printf("%d:%s\n", index++, szResult);
			//qDebug() << QString::fromLocal8Bit(szResult);

			QString path = QString::fromLocal8Bit(szResult);
			qDebug() << index++ << ". "  << path;
			QFileInfo fileInfo(path);
			//qDebug() << "suffix: " << fileInfo.suffix();
			qDebug() << "fileName: " << fileInfo.fileName();
			if (fileInfo.suffix() == QString("doc") || fileInfo.suffix() == QString("docx"))
			{
				mapPaths[QString("doc")].append(path);
			}
			else if (fileInfo.suffix() == QString("ppt") || fileInfo.suffix() == QString("pptx"))
			{
				mapPaths[QString("ppt")].append(path);
			}
			else if (fileInfo.suffix() == QString("wps"))	// .doc
			{
				mapPaths[QString("wps")].append(path);
			}
			else if (fileInfo.suffix() == QString("dps"))	// .ppt
			{
				mapPaths[QString("dps")].append(path);
			}
			delete[] szResult;
		} 

		pMoniker->Release();
	}

	pbc->Release();
	pEnumMoniker->Release();
	pRot->Release();

	CoUninitialize();
	return true;
}

#include <QProcess>
int main(int argc, char* argv[])
{
	QMap<QString, QPair<QString, QStringList>> tt;
	QMap<QString, QStringList> mapPaths;
	GetAllOfficeFilePath(mapPaths);

	qDebug() << endl << "begin: " << endl;
	for (auto &itPathList : mapPaths)
	{
		for (auto &path : itPathList)
		{
			qDebug() << path;
		}
	}
	//for (auto &word : mapPaths[QString("doc")])
	//{
	//	qDebug() << word;
	//
	//}
	//for (auto &ppt : mapPaths[QString("ppt")])
	//{
	//	qDebug() << ppt;
	//}
	//QProcess process;
	//process.start("C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Word 2016.lnk E:/Document/副本.docx");
	//QString txt("C:/WINDOWS/system32/notepad.exe");
	//QProcess::execute("C:/WINDOWS/system32/notepad.exe");
	//process.start(txt);

	//QFile file("test - 副本.docx");
	//file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
	//file.write("hi hi");
	//file.close();

	system("pause");
	return 0;
}
