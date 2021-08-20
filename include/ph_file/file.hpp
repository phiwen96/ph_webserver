#pragma once
#include <ph_concepts/concepts.hpp>
#include "common.hpp"

namespace ph::file {
    
    auto read (String auto& path) -> void
    {
        FILE* file = fopen (path, "rb");
        
        if (file == NULL)
        {
            return nullptr;
            fprintf (stderr, "Could not open file because of existance or access rights\"%s\".\n", path);
            exit (74);
        }
        
        // we seek to the very end using fseek()
        fseek (file, 0L, SEEK_END);
        
        // we call ftell() which tells us how many bytes we are from the start of the file
        size_t fileSize = ftell (file);
        rewind (file);
        
        char* buffer = (char*) malloc (fileSize + 1);
        
        if (buffer == NULL)
        {
            return nullptr;
            fprintf (stderr, "Not enough memory to read \"%s\".\n", path);
            exit (74);
        }
        
        
        size_t bytesRead = fread (buffer, sizeof (char), fileSize, file);
        
        if (bytesRead < fileSize)
        {
            return nullptr;
            fprintf (stderr, "Could not read file \"%s\".\n", path);
            exit (74);
        }
        
        buffer [bytesRead] = '\0';
        
        fclose (file);
        return buffer;
    }
    
    
    
}
