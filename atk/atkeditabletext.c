/* ATK - The Accessibility Toolkit for GTK+
 * Copyright 2001 Sun Microsystems Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "atkeditabletext.h"


struct _AtkEditableTextIfaceClass
{
  GObjectClass parent;
};

typedef struct _AtkEditableTextIfaceClass AtkEditableTextIfaceClass;

GType
atk_editable_text_get_type ()
{
  static GType type = 0;

  if (!type) {
    static const GTypeInfo tinfo =
    {
      sizeof (AtkEditableTextIface),
      (GBaseInitFunc) NULL,
      (GBaseFinalizeFunc) NULL,

    };

    type = g_type_register_static (G_TYPE_INTERFACE, "AtkEditableText", &tinfo, 0);
  }

  return type;
}

/**
 * atk_editable_text_set_attributes:
 * @text: an #AtkEditableText
 * @start_pos: start position
 * @end_pos: end position
 * @attributes: a #PangoAttrList to set for text between @start_pos and @end_pos
 *
 * Set attributes for text between @start_pos and @end_pos.  The characters
 * whose attributes are set are those characters at positions from @start_pos
 * up to, but not including @end_pos. If @end_pos is negative, then the
 * characters selected will be those characters from start_pos to 
 * the end of the text.
 **/
void 
atk_editable_text_set_attributes (AtkEditableText  *text,
                                  gint             start_pos,
                                  gint             end_pos,
                                  PangoAttrList    *attributes)
{
  AtkEditableTextIface *iface;

  g_return_if_fail (text != NULL);
  g_return_if_fail (ATK_IS_EDITABLE_TEXT (text));

  iface = ATK_EDITABLE_TEXT_GET_IFACE (text);

  if (iface->set_attributes)
    (*(iface->set_attributes)) (text, start_pos, end_pos, attributes);
}

/**
 * atk_editable_text_set_text_contents:
 * @text: an #AtkEditableText
 * @string: string to set for text contents of @text
 *
 * Set text contents of @text
 **/
void 
atk_editable_text_set_text_contents (AtkEditableText  *text,
                                     const gchar      *string)
{
  AtkEditableTextIface *iface;

  g_return_if_fail (text != NULL);
  g_return_if_fail (ATK_IS_EDITABLE_TEXT (text));

  iface = ATK_EDITABLE_TEXT_GET_IFACE (text);

  if (iface->set_text_contents)
    (*(iface->set_text_contents)) (text, string);
}

/**
 * atk_editable_text_insert_text:
 * @text: an #AtkEditableText
 * @string: the text to insert
 * @length: the length of text to insert, in bytes
 * @position: The caller initializes this to 
 * the position at which to insert the text. After the call it
 * points at the position after the newly inserted text.
 *
 * Insert text at a given position
 **/
void 
atk_editable_text_insert_text (AtkEditableText  *text,
                               const gchar      *string,
                               gint             length,
                               gint             *position)
{
  AtkEditableTextIface *iface;

  g_return_if_fail (text != NULL);
  g_return_if_fail (ATK_IS_EDITABLE_TEXT (text));

  iface = ATK_EDITABLE_TEXT_GET_IFACE (text);

  if (iface->insert_text)
    (*(iface->insert_text)) (text, string, length, position);
}

/**
 * atk_editable_text_copy_text:
 * @text: an #AtkEditableText
 * @start_pos: start position
 * @end_pos: end position
 *
 * Copy text from @start_pos up to, but not including @end_pos 
 * to the clipboard.
 **/
void 
atk_editable_text_copy_text (AtkEditableText  *text,
                             gint             start_pos,
                             gint             end_pos)
{
  AtkEditableTextIface *iface;

  g_return_if_fail (text != NULL);
  g_return_if_fail (ATK_IS_EDITABLE_TEXT (text));

  iface = ATK_EDITABLE_TEXT_GET_IFACE (text);

  if (iface->copy_text)
    (*(iface->copy_text)) (text, start_pos, end_pos);
}

/**
 * atk_editable_text_cut_text:
 * @text: an #AtkEditableText
 * @start_pos: start position
 * @end_pos: end position
 *
 * Copy text from @start_pos up to, but not including @end_pos
 * to the clipboard and then delete from the widget.
 **/
void 
atk_editable_text_cut_text  (AtkEditableText  *text,
                             gint             start_pos,
                             gint             end_pos)
{
  AtkEditableTextIface *iface;

  g_return_if_fail (text != NULL);
  g_return_if_fail (ATK_IS_EDITABLE_TEXT (text));

  iface = ATK_EDITABLE_TEXT_GET_IFACE (text);

  if (iface->cut_text)
    (*(iface->cut_text)) (text, start_pos, end_pos);
}

/**
 * atk_editable_text_delete_text:
 * @text: an #AtkEditableText
 * @start_pos: start position
 * @end_pos: end position
 *
 * Delete text @start_pos up to, but not including @end_pos
 **/
void 
atk_editable_text_delete_text (AtkEditableText  *text,
                               gint             start_pos,
                               gint             end_pos)
{
  AtkEditableTextIface *iface;

  g_return_if_fail (text != NULL);
  g_return_if_fail (ATK_IS_EDITABLE_TEXT (text));

  iface = ATK_EDITABLE_TEXT_GET_IFACE (text);

  if (iface->delete_text)
    (*(iface->delete_text)) (text, start_pos, end_pos);
}

/**
 * atk_editable_text_paste_text:
 * @text: an #AtkEditableText
 * @position: position to paste
 *
 * Paste text from clipboard to specified @position 
 **/
void 
atk_editable_text_paste_text (AtkEditableText  *text,
                              gint             position)
{
  AtkEditableTextIface *iface;

  g_return_if_fail (text != NULL);
  g_return_if_fail (ATK_IS_EDITABLE_TEXT (text));

  iface = ATK_EDITABLE_TEXT_GET_IFACE (text);

  if (iface->paste_text)
    (*(iface->paste_text)) (text, position);
}
