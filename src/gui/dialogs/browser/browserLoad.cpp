/* -----------------------------------------------------------------------------
 *
 * Giada - Your Hardcore Loopmachine
 *
 * -----------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2018 Giovanni A. Zuliani | Monocasual
 *
 * This file is part of Giada - Your Hardcore Loopmachine.
 *
 * Giada - Your Hardcore Loopmachine is free software: you can
 * redistribute it and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * Giada - Your Hardcore Loopmachine is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Giada - Your Hardcore Loopmachine. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------------- */


#include "../../../utils/fs.h"
#include "../../elems/browser.h"
#include "../../elems/basics/button.h"
#include "../../elems/basics/input.h"
#include "browserLoad.h"


using std::string;
using namespace giada;


gdBrowserLoad::gdBrowserLoad(int x, int y, int w, int h, const string& title,
		const string& path, void (*cb)(void*), m::Channel* ch)
	:	gdBrowserBase(x, y, w, h, title, path, cb)
{
	channel = ch;

	where->size(groupTop->w()-updir->w()-8, 20);

	browser->callback(cb_down, (void*) this);

	ok->label("Load");
	ok->callback(cb_load, (void*) this);
	ok->shortcut(FL_ENTER);

	/* On OS X the 'where' input doesn't get resized properly on startup. Let's 
	force it. */
	
	where->redraw();
}


/* -------------------------------------------------------------------------- */


void gdBrowserLoad::cb_load(Fl_Widget* v, void* p) { ((gdBrowserLoad*)p)->cb_load(); }
void gdBrowserLoad::cb_down(Fl_Widget* v, void* p) { ((gdBrowserLoad*)p)->cb_down(); }


/* -------------------------------------------------------------------------- */


void gdBrowserLoad::cb_load()
{
	callback((void*) this);
}


/* -------------------------------------------------------------------------- */


void gdBrowserLoad::cb_down()
{
	string path = browser->getSelectedItem();

	if (path.empty() || !gu_isDir(path)) // when click on an empty area or not a dir
		return;

	browser->loadDir(path);
	where->value(browser->getCurrentDir().c_str());
}
