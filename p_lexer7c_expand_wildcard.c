#include "minishell.h"

static int expand_wildcard_recursive(t_wc_args *a, char *path, char *pattern, t_ma *ma);
static int process_entry(t_wc_args *a, char *path, char *entry_name, char *pattern, t_ma *ma);
static int process_directory(t_wc_args *a, char *dir_path, char *pattern, t_ma *ma);

/**
 * @brief Expands wildcard patterns in a given path.
 * 
 * This function expands wildcard patterns in the given path. If the path contains
 * a directory separator ('/'), it splits the path into a directory path and a pattern,
 * then calls the recursive expansion function. Otherwise, it processes the current
 * directory with the given pattern.
 * 
 * @param a Pointer to the wildcard arguments structure.
 * @param pattern The pattern to be expanded.
 * @param ma Pointer to the memory allocation structure.
 * @return int Returns 1 on success, 0 on failure.
 * 
 * @note This function uses ft_strrchr to find the last occurrence of '/'.
 * @note If memory allocation fails during the process, the function returns 0.
*/
int expand_wildcard(t_wc_args *a, char *pattern, t_ma *ma)
{
    char *path_end;
    char *dir_path;
    
    path_end = ft_strrchr(pattern, '/');
    if (path_end == NULL)
        return (process_directory(a, ".", pattern, ma));
    dir_path = ft_strndup_g_c(pattern, path_end - pattern, &(ma->first_node));
    if (!dir_path)
        return (0);
    path_end++;
    return (expand_wildcard_recursive(a, dir_path, path_end, ma));
}

/**
 * @brief Recursively expands wildcard patterns in a directory.
 * 
 * This function opens the given directory and processes each entry,
 * recursively expanding wildcards in subdirectories if necessary.
 * 
 * @param a Pointer to the wildcard arguments structure.
 * @param path The current directory path.
 * @param pattern The pattern to match against.
 * @param ma Pointer to the memory allocation structure.
 * @return int Returns 1 on success, 0 on failure.
 * 
 * @note This function uses opendir and readdir to iterate through directory entries.
 * @note Hidden files (starting with '.') are skipped unless the pattern explicitly includes them.
 * @note If processing any entry fails, the function stops and returns 0.
*/
static int expand_wildcard_recursive(t_wc_args *a, char *path, char *pattern, t_ma *ma)
{
    DIR *dir;
    struct dirent *entry;
    int result = 1;

    dir = opendir(path);
    if (!dir)
        return (0);
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] == '.' && (pattern[0] != '.' || pattern[1] != '*'))
            continue;
        if (!process_entry(a, path, entry->d_name, pattern, ma))
        {
            result = (0);
            break;
        }
    }
    closedir(dir);
    return (result);
}

/**
 * @brief Processes a single directory entry for wildcard expansion.
 * 
 * This function checks if the given entry matches the pattern. If it's a directory
 * and matches, it recursively expands wildcards in that directory. If it's a file
 * and matches, it adds the file to the results.
 * 
 * @param a Pointer to the wildcard arguments structure.
 * @param path The current directory path.
 * @param entry_name The name of the current entry.
 * @param pattern The pattern to match against.
 * @param ma Pointer to the memory allocation structure.
 * @return int Returns 1 on success, 0 on failure.
 * 
 * @note This function uses stat to determine if the entry is a directory.
 * @note If memory allocation fails during path joining, the function returns 0.
*/
static int process_entry(t_wc_args *a, char *path, char *entry_name, char *pattern, t_ma *ma)
{
    char *full_path;
    struct stat (st);

    full_path = ft_strjoin_g_c(path, "/", &(ma->first_node));
    full_path = ft_strjoin_g_c(full_path, entry_name, &(ma->first_node));
    if (!full_path)
        return (0);
    if (stat(full_path, &st) != 0)
        return (1);
    if (S_ISDIR(st.st_mode) && match_pattern(entry_name, pattern))
        return expand_wildcard_recursive(a, full_path, "*", ma);
    else if (match_pattern(entry_name, pattern))
        return add_single_element(a, full_path, ma);
    return (1);
}

/**
 * @brief Processes a directory for wildcard expansion.
 * 
 * This function opens the given directory and processes each entry that matches
 * the given pattern, adding matching entries to the results.
 * 
 * @param a Pointer to the wildcard arguments structure.
 * @param dir_path The directory path to process.
 * @param pattern The pattern to match against.
 * @param ma Pointer to the memory allocation structure.
 * @return int Returns 1 on success, 0 on failure.
 * 
 * @note This function uses opendir and readdir to iterate through directory entries.
 * @note Hidden files (starting with '.') are skipped unless the pattern explicitly includes them.
 * @note If adding any matching entry fails, the function stops and returns 0.
*/
static int process_directory(t_wc_args *a, char *dir_path, char *pattern, t_ma *ma)
{
    DIR *dir;
    struct dirent *entry;
    int result = 1;

    dir = opendir(dir_path);
    if (!dir)
        return 0;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] == '.' && (pattern[0] != '.' || pattern[1] != '*'))
            continue;
        if (match_pattern(entry->d_name, pattern))
            if (!add_matching_entry(a, dir_path, entry->d_name, ma))
            {
                result = 0;
                break;
            }
    }
    closedir(dir);
    return (result);
}