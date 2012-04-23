/*
 * popupmenu.c
 * This file is part of Ftjerm
 *
 * Copyright (C) 2007-2010 - Kristopher Wilson, Stjepan Glavina and Markus Groß
 * 
 * Ftjerm is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Ftjerm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Ftjerm; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 */

#include <gtk/gtk.h>
#include <vte/vte.h>
#include <string.h>
#include "ftjerm.h"



extern GtkWidget *mainwindow;
extern int activetab;
extern GArray* tabs;
GtkWidget *popupmenu= NULL;
gboolean popupmenu_shown;

GtkWidget *close_tab;

void show_about_dialog();
void build_popupmenu(void);
static void popupmenu_activate(gchar*);
static void popupmenu_deactivate(GtkMenuShell*, gpointer);

void build_popupmenu(void)
{
    popupmenu = gtk_menu_new();
    popupmenu_shown = FALSE;

    GtkWidget *menuitem;
    GtkWidget *img;

    gchar *labels[] = {"New Tab", "Close Tab", "Copy", "Paste", "Toggle Fullscreen", "About", "Quit"};
    gchar *stocks[] = {GTK_STOCK_ADD, GTK_STOCK_CLOSE, GTK_STOCK_COPY,
        GTK_STOCK_PASTE, GTK_STOCK_FULLSCREEN, GTK_STOCK_ABOUT, GTK_STOCK_QUIT};

    int i;
    
    for(i = 0; i < 7; i++)
    {
        if(i == 2 || i == 4 || i == 5)
        {
            menuitem = gtk_separator_menu_item_new();
            gtk_menu_shell_append(GTK_MENU_SHELL(popupmenu), menuitem);
            gtk_widget_show(GTK_WIDGET(menuitem));
        }

        menuitem = gtk_image_menu_item_new_with_label(labels[i]);
        img = gtk_image_new_from_stock(stocks[i], GTK_ICON_SIZE_MENU);
        
        if(i == 1)
        {
            close_tab = menuitem;
            gtk_widget_set_sensitive(menuitem, FALSE);
        }
        
        gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(menuitem),
            GTK_WIDGET(img));
        
        g_signal_connect_swapped(G_OBJECT(menuitem), "activate",
            G_CALLBACK(popupmenu_activate), (gpointer)labels[i]);
        
        gtk_menu_shell_append(GTK_MENU_SHELL(popupmenu), menuitem);
        gtk_widget_show(GTK_WIDGET(menuitem));
    }

    g_signal_connect_swapped(G_OBJECT(popupmenu), "deactivate",
        G_CALLBACK(popupmenu_deactivate), NULL);
}

static void popupmenu_activate(gchar *label)
{
    if(!strcmp(label, "New Tab"))
    {
        mainwindow_create_tab();
    }
    else if(!strcmp(label, "Close Tab"))
    {
        mainwindow_close_tab(NULL);
    }
    else if(!strcmp(label, "Copy"))
    {
        vte_terminal_copy_clipboard(g_array_index(tabs, VteTerminal*, activetab));
    }
    else if(!strcmp(label, "Paste"))
    {
        vte_terminal_paste_clipboard(g_array_index(tabs, VteTerminal*, activetab));
    }
    else if(!strcmp(label, "Toggle Fullscreen"))
    {
        mainwindow_toggle_fullscreen();
    }
    else if(!strcmp(label, "Quit"))
    {
        gtk_widget_destroy(GTK_WIDGET(mainwindow));
    } else if(!strcmp(label, "About")) {
        show_about_dialog();
    }

    popupmenu_shown = FALSE;
}

void show_about_dialog() {
    GtkWidget *dialog;
    dialog = gtk_dialog_new();
    
    #if GTK_CHECK_VERSION(2, 4, 0)
        gtk_dialog_set_has_separator(GTK_DIALOG(dialog), FALSE);
        gtk_container_set_border_width(GTK_CONTAINER(dialog), 5);
        gtk_box_set_spacing(GTK_BOX(GTK_DIALOG(dialog)->vbox), 5);
    #endif
    
    gtk_dialog_add_button(GTK_DIALOG(dialog), 
    #if GTK_CHECK_VERSION(2, 4, 0)
        GTK_STOCK_CLOSE, GTK_RESPONSE_CLOSE);
    #else
        GTK_STOCK_OK, GTK_RESPONSE_CLOSE);
    #endif
    
    gtk_dialog_set_default_response(GTK_DIALOG(dialog), GTK_RESPONSE_CLOSE);
    g_signal_connect(G_OBJECT(dialog), "response", G_CALLBACK(gtk_widget_destroy), dialog);

    GtkWidget *vbox = gtk_vbox_new(FALSE, 8); 
    #if GTK_CHECK_VERSION(2, 4, 0)
        gtk_container_set_border_width(GTK_CONTAINER(vbox), 5);
    #else
        gtk_container_set_border_width(GTK_CONTAINER(vbox), 8);
    #endif
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), vbox, TRUE, TRUE, 0);
    
    GtkWidget *name_and_version = gtk_label_new(NULL);
    gtk_label_set_selectable(GTK_LABEL(name_and_version), TRUE);
    gtk_label_set_justify(GTK_LABEL(name_and_version), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(vbox), name_and_version, FALSE, FALSE, 0);
    
    GtkWidget *forked_from = gtk_label_new(NULL);
    gtk_label_set_selectable(GTK_LABEL(forked_from), TRUE);
    gtk_label_set_justify(GTK_LABEL(forked_from), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(vbox), forked_from, FALSE, FALSE, 0);
    
    GtkWidget *author = gtk_label_new(NULL);
    gtk_label_set_selectable(GTK_LABEL(author), TRUE);
    gtk_label_set_justify(GTK_LABEL(author), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(vbox), author, FALSE, FALSE, 0);
    
    gchar *s_name_and_version = g_strdup_printf("<span size=\"xx-large\" weight=\"bold\">Ftjerm %s (fork of Stjerm)</span>", FTJERM_VERSION);
    gtk_label_set_markup(GTK_LABEL(name_and_version), s_name_and_version);
    g_free(s_name_and_version);
    
    gchar *s_forked_from = g_strdup_printf("<span size=\"x-large\" weight=\"normal\">Quake-like terminal emulator</span>");
    gtk_label_set_markup(GTK_LABEL(forked_from), s_forked_from);
    g_free(s_forked_from);
    
    gchar *s_author = g_strdup_printf("<span size=\"medium\" weight=\"normal\">Author: Holden Cox, 2012</span>");
    gtk_label_set_markup(GTK_LABEL(author), s_author);
    g_free(s_author);
    
    gtk_widget_show_all(vbox);
    gtk_window_set_title(GTK_WINDOW(dialog), "About Fjterm");
    gtk_dialog_run (GTK_DIALOG (dialog));
}

static void popupmenu_deactivate(GtkMenuShell *menushell, gpointer userdata)
{
    popupmenu_shown = FALSE;
}

