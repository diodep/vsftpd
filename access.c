/*
 * Part of Very Secure FTPd
 * Licence: GPL v2
 * Author: Chris Evans
 * access.c
 *
 * Routines to do very very simple access control based on filenames.
 */

#include "access.h"
#include "ls.h"
#include "tunables.h"
#include "str.h"

int
vsf_access_check_file(const struct mystr* p_filename_str)
{
  static struct mystr s_access_str;
  static struct mystr s_prefix_str;
  unsigned int iters = 0;

  if (!tunable_deny_file && !tunable_allow_prefix)
  {
    return 1;
  }
  if (tunable_deny_file)
  {
    if (str_isempty(&s_access_str))
    {
      str_alloc_text(&s_access_str, tunable_deny_file);
    }
    if (vsf_filename_passes_filter(p_filename_str, &s_access_str, &iters))
    {
      return 0;
    }
    else
    {
      struct str_locate_result loc_res =
        str_locate_str(p_filename_str, &s_access_str);
      if (loc_res.found)
      {
        return 0;
      }
    }
  }

  if (tunable_allow_prefix)
  {
    if (str_isempty(&s_prefix_str))
    {
      str_alloc_text(&s_prefix_str, tunable_allow_prefix);
    }
    iters = 0;
    if (vsf_prefix_passes_filter(p_filename_str, &s_prefix_str, &iters) == 0)
    {
      return 0;
    }
  }

  return 1;
}

int
vsf_access_check_file_visible(const struct mystr* p_filename_str)
{
  static struct mystr s_access_str;
  static struct mystr s_prefix_str;
  unsigned int iters = 0;

  if (!tunable_hide_file && !tunable_allow_prefix)
  {
    return 1;
  }
  if (tunable_hide_file)
  {
    if (str_isempty(&s_access_str))
    {
      str_alloc_text(&s_access_str, tunable_hide_file);
    }
    if (vsf_filename_passes_filter(p_filename_str, &s_access_str, &iters))
    {
      return 0;
    }
    else
    {
      struct str_locate_result loc_res =
        str_locate_str(p_filename_str, &s_access_str);
      if (loc_res.found)
      {
        return 0;
      }
    }
  }

  if (tunable_allow_prefix)
  {
    if (str_isempty(&s_prefix_str))
    {
      str_alloc_text(&s_prefix_str, tunable_allow_prefix);
    }
    iters = 0;
    if (vsf_prefix_passes_filter(p_filename_str, &s_prefix_str, &iters) == 0)
    {
      return 0;
    }
  }

  return 1;
}

