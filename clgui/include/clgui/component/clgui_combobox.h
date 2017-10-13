#pragma once

#include "clgui/core/clgui_macro.h"
#include "clgui/core\clgui_variable.h"
#include "clgui/core/clgui_object.h"


CLGUI_NAMESPACE_START

class CLGUI_API clguiComboBox:public clguiComponent{
public:
clguiComboBox();
void AppendLabel(clstr label);
void AppendLabel(const clchar* label);
void AppendLabel(std::vector<clstr>);
void AppendLabel(std::vector<const clchar*>);

void ClearAllLabels();
clint GetSelectedIndex()const;
clstr GetSelectedLabel()const;
clbool SetSelection(clint index);

protected:
  ~clguiComboBox();
  void Render()override;
  void PostRender()override;

private:
  cvInt m_selectedIndex;
  clstr m_sRenderList="";
  std::vector<clstr> m_labels;
};

CLGUI_NAMESPACE_END