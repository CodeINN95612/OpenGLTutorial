#pragma once
#include <Engine/Engine.hpp>

class PanelObjetos
{
public:
	PanelObjetos() = default;
	virtual ~PanelObjetos() = default;

	PanelObjetos(const PanelObjetos& other) = delete;
	PanelObjetos& operator==(const PanelObjetos& other) = delete;

	static std::shared_ptr<GL::ObjetoJuego>& Render(std::vector<std::shared_ptr<GL::ObjetoJuego>>& objetos)
	{
		ImGui::Begin("Objetos");
		for (std::shared_ptr<GL::ObjetoJuego>& objeto : objetos)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
			flags |= objeto == m_Seleccionado ? ImGuiTreeNodeFlags_Selected : 0;
			flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

			bool opened = ImGui::TreeNodeEx(objeto->Etiqueta().etiqueta.c_str(), flags);
			if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
			{
				m_Seleccionado = objeto;
			}
			if (opened)
			{
				ImGui::TreePop();
			}
		}
		ImGui::End();
		return m_Seleccionado;
	}

private:
	inline static std::shared_ptr<GL::ObjetoJuego> m_Seleccionado = {};
};
