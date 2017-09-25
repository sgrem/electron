// Copyright (c) 2017 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "atom/browser/native_browser_view_views.h"

#include "brightray/browser/inspectable_web_contents_view.h"
#include "ui/gfx/geometry/rect.h"
#include "ui/views/background.h"
#include "ui/views/view.h"

namespace atom {

NativeBrowserViewViews::NativeBrowserViewViews(
    brightray::InspectableWebContentsView* web_contents_view)
    : NativeBrowserView(web_contents_view) {}

NativeBrowserViewViews::~NativeBrowserViewViews() {}

void NativeBrowserViewViews::OnParentWidgetBoundsChanged() {
  const auto flags = GetAutoResizeFlags();
  int width_delta = 0;
  int height_delta = 0;
  if (flags & kAutoResizeWidth) {
    width_delta = new_bounds.width() - widget_size_.width();
  }
  if (flags & kAutoResizeHeight) {
    height_delta = new_bounds.height() - widget_size_.height();
  }

  auto* view = GetInspectableWebContentsView()->GetView();
  auto new_view_size = view->size();
  new_view_size.set_width(new_view_size.width() + width_delta);
  new_view_size.set_height(new_view_size.height() + height_delta);
  view->SetSize(new_view_size);
}

void NativeBrowserViewViews::SetBounds(const gfx::Rect& bounds) {
  auto* view = GetInspectableWebContentsView()->GetView();
  view->SetBoundsRect(bounds);
}

void NativeBrowserViewViews::SetBackgroundColor(SkColor color) {
  auto* view = GetInspectableWebContentsView()->GetView();
  view->set_background(views::Background::CreateSolidBackground(color));
}

// static
NativeBrowserView* NativeBrowserView::Create(
    brightray::InspectableWebContentsView* web_contents_view) {
  return new NativeBrowserViewViews(web_contents_view);
}

}  // namespace atom
