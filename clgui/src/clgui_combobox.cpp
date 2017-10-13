#include "clgui/component/clgui_combobox.h"
#include "imgui\imgui.h"

CLGUI_NAMESPACE_START

clguiComboBox::clguiComboBox()
  :clguiComponent(CLGUI_OBJECT_TYPE_COMPONENT)
  ,m_selectedIndex(0){
  m_size.Set(60,20);
}

void clguiComboBox::AppendLabel(clstr label){
  m_labels.push_back(label);
  m_sRenderList="";
  const clsize N{m_labels.size()};
  for(clint i=0;i<N;i++){
    m_sRenderList.append(m_labels[i]);
    m_sRenderList.append(1,'\0');
  }
}

void clguiComboBox::AppendLabel(const clchar * label){
  m_labels.push_back(label);
  m_sRenderList="";
  const clsize N{m_labels.size()};
  for(clint i=0;i<N;i++){
    m_sRenderList.append(m_labels[i]);
    m_sRenderList.append(1,'\0');
  }
}

void clguiComboBox::AppendLabel(std::vector<clstr> data){
  const clsize M{data.size()};
  for(clint i=0;i<M;i++){
    m_labels.push_back(data[i]);
  }
  m_sRenderList="";
  const clsize N{m_labels.size()};
  for(clint i=0;i<N;i++){
    m_sRenderList.append(m_labels[i]);
    m_sRenderList.append(1,'\0');
  }
}

void clguiComboBox::AppendLabel(std::vector<const clchar*> data){
  const clsize M{data.size()};
  for(clint i=0;i<M;i++){
    m_labels.push_back(data[i]);
  }
  m_sRenderList="";
  const clsize N{m_labels.size()};
  for(clint i=0;i<N;i++){
    m_sRenderList.append(m_labels[i]);
    m_sRenderList.append(1,'\0');
  }
}

void clguiComboBox::ClearAllLabels(){
  m_labels.clear();
  m_selectedIndex.ResetTo(0);
}

clint clguiComboBox::GetSelectedIndex() const{
  return m_selectedIndex[0];
}

clstr clguiComboBox::GetSelectedLabel() const{
  clint index=m_selectedIndex[0];
  if(index<0)return "";
  else return m_labels[index];
}

clbool clguiComboBox::SetSelection(clint index){
  if(index>=m_labels.size())return false;
  m_selectedIndex.ResetTo(index);
  return true;
}

clguiComboBox::~clguiComboBox(){
  m_labels.clear();
}

void clguiComboBox::Render(){
  if(m_size.x>0){
    ImGui::PushItemWidth(m_size.x);
    ImGui::Combo(m_sRenderName.c_str(),m_selectedIndex[0],m_sRenderList.c_str());
    ImGui::PopItemWidth();
  } else{
    ImGui::Combo(m_sRenderName.c_str(),m_selectedIndex[0],m_sRenderList.c_str());
  }
}

void clguiComboBox::PostRender(){
  if(m_selectedIndex.CheckChange()){
    clguiEventComboBoxStatusChange evt(this,clguiEventType::EVT_COMBOBOX_STATUS_CHANGE);
    DispatchEvent_(&evt);
    m_selectedIndex.Update();
  }
}

CLGUI_NAMESPACE_END
