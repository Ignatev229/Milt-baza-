#include "AppUtility.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>

bool copyFolderRecursively(const QString& srcFolderPath, const QString& destFolderPath)
{
	QDir sourceDir(srcFolderPath);
	if (!sourceDir.exists()) {
        return false; // Source directory does not exist // Исходный  Директорий не существует
	}

	QDir destDir(destFolderPath);
	if (!destDir.exists()) {
        destDir.mkpath("."); // Create destination directory // Создать целевой  Директорию
	}

	QFileInfoList fileInfoList = sourceDir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
	foreach(const QFileInfo & fileInfo, fileInfoList) {
		QString srcFilePath = fileInfo.filePath();
		QString destFilePath = destFolderPath + QDir::separator() + fileInfo.fileName();

		if (fileInfo.isDir()) {
            // Recursively copy subdirectories // Рекурсивно копировать подкаталоги
			if (!copyFolderRecursively(srcFilePath, destFilePath)) {
				return false;
			}
		}
		else if (fileInfo.isFile()) {
            // Copy files // Копировать файлы
			if (!QFile::copy(srcFilePath, destFilePath)) {
				return false;
			}
		}
	}
	return true;
}
