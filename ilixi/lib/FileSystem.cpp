/*
 Copyright 2011 Tarik Sekmen.

 All Rights Reserved.

 Written by Tarik Sekmen <tarik@ilixi.org>.

 This file is part of ilixi.

 ilixi is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 ilixi is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with ilixi.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "FileSystem.h"
#include <libgen.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "core/Logger.h"

namespace ilixi
{
  namespace FileSystem
  {
    bool
    fileExists(const std::string& path)
    {
      if (access(path.c_str(), F_OK) != 0)
        return false;
      return true;
    }

    bool
    dirExists(const std::string& path)
    {
      const char *myDir = dirname(const_cast<char*>(path.c_str()));
      struct stat myStat;
      if ((stat(myDir, &myStat) == 0)
          && (((myStat.st_mode) & S_IFMT) == S_IFDIR))
        return true;
      return false;
    }

    bool
    renameFile(const std::string& oldName, const std::string& newName)
    {
      if (rename(oldName.c_str(), newName.c_str()) == 0)
        return true;
      return false;
    }

    bool
    deleteFile(const std::string& path)
    {
      if (unlink(path.c_str()) == 0)
        return true;
      return false;
    }

    bool
    deleteDirectory(const std::string& path)
    {
      if (rmdir(path.c_str()) == 0)
        return true;
      return false;
    }

    long long
    getFileSize(const std::string& path)
    {
      struct stat filestatus;
      if (stat(path.c_str(), &filestatus) == 0)
        return filestatus.st_size;
      return 0;
    }

    time_t
    getModificationTime(const std::string& path)
    {
      struct stat filestatus;
      if (stat(path.c_str(), &filestatus) == 0)
        return filestatus.st_mtime;
      time_t t;
      return t;
    }

    std::string
    homeDirectory()
    {
      const char *home = getenv("HOME");
      if (!home)
        {
          home = getenv("TMPDIR");
          if (!home)
            home = "/tmp";
        }
      return std::string(home);
    }

    std::string
    directoryName(const std::string& path)
    {
      return std::string(dirname(const_cast<char*>(path.c_str())));
    }

    std::string
    fileName(const std::string& path)
    {
      return std::string(basename(const_cast<char*>(path.c_str())));
    }

    std::vector<std::string>
    listDirectory(const std::string& path)
    {
      std::vector<std::string> entries;
      return entries;
    }

    FILE*
    temporaryFile(const std::string& prefix)
    {
      char buffer[L_tmpnam];
      tmpnam(buffer);
      FILE * pFile;
      pFile = tmpfile();
      return pFile;
    }

    void
    closeFile(FILE* handle)
    {
      fclose(handle);
    }
  }

} /* namespace ilixi */