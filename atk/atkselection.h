/* ATK -  Accessibility Toolkit
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

#ifndef __ATK_SELECTION_H__
#define __ATK_SELECTION_H__

#include <atk/atkobject.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
 * This AtkSelection interface provides the standard mechanism for an 
 * assistive technology to determine what the current selected children are, 
 * as well as modify the selection set. Any object that has children that 
 * can be selected should support the AtkSelection interface.
 */

#define ATK_TYPE_SELECTION                        (atk_selection_get_type ())
#define ATK_IS_SELECTION(obj)                     G_TYPE_CHECK_INSTANCE_TYPE ((obj), ATK_TYPE_SELECTION)
#define ATK_SELECTION(obj)                        G_TYPE_CHECK_INSTANCE_CAST ((obj), ATK_TYPE_SELECTION, AtkSelection)
#define ATK_SELECTION_GET_IFACE(obj)              (G_TYPE_INSTANCE_GET_INTERFACE ((obj), ATK_TYPE_SELECTION, AtkSelectionIface))

#ifndef _TYPEDEF_ATK_SELECTION_
#define _TYPEDEF_ATK_SELECTION_
typedef struct _AtkSelection AtkSelection;
#endif
typedef struct _AtkSelectionIface AtkSelectionIface;

struct _AtkSelectionIface
{
  GTypeInterface parent;

  /*
   * Adds the specified accessible child of the object to the
   * object's selection.
   */
  void         (* add_selection)        (AtkSelection   *selection,
                                         gint           i);
  /*
   * Clears the selection in the object so that no children in the object
   * are selected.
   */
  void         (* clear_selection)      (AtkSelection   *selection);
  /*
   * Returns a reference to the accessible object representing the specified 
   * selected * child of the object.
   */
  AtkObject*   (* ref_selection)        (AtkSelection   *selection,
                                         gint           i);
  /*
   * Returns the number of accessible children currently selected.
   */
  gint         (* get_selection_count)  (AtkSelection   *selection);
  /*
   * Determines if the current child of this object is selected
   */
  gboolean     (* is_child_selected)    (AtkSelection   *selection,
                                         gint           i);
  /*
   * Removes the specified child of the object from the object's selection.
   */
  void         (* remove_selection)     (AtkSelection   *selection,
                                         gint           i);
  /*
   * Causes every child of the object to be selected if the object
   * supports multiple selections.
   */
  void         (* select_all_selection) (AtkSelection   *selection);

};
GType atk_selection_get_type ();

void         atk_selection_add_selection        (AtkSelection   *selection,
                                                 gint           i);

void         atk_selection_clear_selection      (AtkSelection   *selection);

AtkObject*   atk_selection_ref_selection        (AtkSelection   *selection,
                                                 gint           i);

gint         atk_selection_get_selection_count  (AtkSelection   *selection);

gboolean     atk_selection_is_child_selected    (AtkSelection   *selection,
                                                 gint           i);

void         atk_selection_remove_selection     (AtkSelection   *selection,
                                                 gint           i);

void         atk_selection_select_all_selection (AtkSelection   *selection);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __ATK_SELECTION_H__ */
