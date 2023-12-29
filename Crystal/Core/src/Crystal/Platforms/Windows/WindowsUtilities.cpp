#include "crpch.h"
#include "WindowsUtilities.hpp"

#include "Crystal/Core/Application.hpp"

#include <commdlg.h>
#include <Shlobj.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace Crystal
{

	std::string WindowsUtils::OpenFileImplementation(const char* filter, const char* initDir)
	{
		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		CHAR currentDir[256] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
		ofn.lStructSize = sizeof(OPENFILENAMEA);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);

		if (initDir)
		{
			ofn.lpstrInitialDir = initDir;
		}
		else if (GetCurrentDirectoryA(256, currentDir))
		{
			ofn.lpstrInitialDir = currentDir;
		}

		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetOpenFileNameA(&ofn) == TRUE)
			return std::string(ofn.lpstrFile);

		return std::string();
	}

	std::string WindowsUtils::SaveFileImplementation(const char* filter, const char* initDir)
	{
		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		CHAR currentDir[256] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
		ofn.lStructSize = sizeof(OPENFILENAMEA);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);

		if (initDir)
		{
			ofn.lpstrInitialDir = initDir;
		}
		else if (GetCurrentDirectoryA(256, currentDir))
		{
			ofn.lpstrInitialDir = currentDir;
		}

		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

		// Sets the default extension by extracting it from the filter
		ofn.lpstrDefExt = strchr(filter, '\0') + 1;

		if (GetSaveFileNameA(&ofn) == TRUE)
			return std::string(ofn.lpstrFile);

		return std::string();
	}

	float WindowsUtils::GetTimeImplementation()
	{
		return (float)glfwGetTime();
	}

	std::string WindowsUtils::OpenDirectoryImplementation(const char* initDir)
	{
		IFileOpenDialog* fileDialog;
		if (SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&fileDialog))))
		{
			DWORD options;
			if (SUCCEEDED(fileDialog->GetOptions(&options)))
			{
				fileDialog->SetOptions(options | FOS_PICKFOLDERS);
			}

			if (initDir)
			{
				int wideStrLen = MultiByteToWideChar(CP_UTF8, 0, initDir, -1, NULL, 0);
				if (wideStrLen > 0)
				{
					std::wstring wideInitDir(wideStrLen, L'\0');
					MultiByteToWideChar(CP_UTF8, 0, initDir, -1, &wideInitDir[0], wideStrLen);

					IShellItem* initialDirItem;
					if (SUCCEEDED(SHCreateItemFromParsingName(wideInitDir.c_str(), NULL, IID_PPV_ARGS(&initialDirItem))))
					{
						fileDialog->SetFolder(initialDirItem);
						initialDirItem->Release();
					}
				}
			}

			if (SUCCEEDED(fileDialog->Show(NULL)))
			{
				IShellItem* resultItem;
				if (SUCCEEDED(fileDialog->GetResult(&resultItem)))
				{
					PWSTR path;
					if (SUCCEEDED(resultItem->GetDisplayName(SIGDN_FILESYSPATH, &path)))
					{
						// Convert wide string to narrow string
						int narrowStrLen = WideCharToMultiByte(CP_UTF8, 0, path, -1, NULL, 0, NULL, NULL);
						if (narrowStrLen > 0)
						{
							std::string narrowPath(narrowStrLen, '\0');
							WideCharToMultiByte(CP_UTF8, 0, path, -1, &narrowPath[0], narrowStrLen, NULL, NULL);

							CoTaskMemFree(path);
							resultItem->Release();

							return narrowPath;
						}
					}

					CoTaskMemFree(path);
					resultItem->Release();
				}
			}

			fileDialog->Release();
		}

		return std::string();
	}

	void WindowsUtils::CreateDirectoryImplementation(const char* path)
	{
		// Convert narrow-char string to wide-char string
		wchar_t widePath[MAX_PATH];
		mbstowcs(widePath, path, MAX_PATH);

		if (CreateDirectory(widePath, NULL) || ERROR_ALREADY_EXISTS == GetLastError()) 
		{
			return;
		}
		CR_CORE_ERROR("Failed to create directory: {0}", path);
	}

}