#include "bbzlpch.h"
#include "DebugPanel.h"

#include <Bamboozle/Log.h>
#include <imgui.h>

namespace bbzl
{
	void DebugPanel::registerSection(const std::string& str, const FnSectionFunc& section)
	{
		[[maybe_unused]] auto it = std::find_if(m_sections.begin(), m_sections.end(), [&str](const auto& section){ return section.name == str; });
		BBZL_ASSERT(it == m_sections.cend());

		m_sections.emplace_back(str, section);
	}

	void DebugPanel::unregisterSection(const std::string& str)
	{
		auto it = std::find_if(m_sections.begin(), m_sections.end(), [&str](const auto& section){ return section.name == str; });
		if (it != m_sections.end())
		{
			*it = m_sections.back();
			m_sections.pop_back();
		}
		else
		{
			BBZL_CORE_WARN("unregisterSection: section {} not found");
		}
	}

	void DebugPanel::render()
	{
		ImGui::Begin("Debug panel");

		for (auto& section : m_sections)
		{
			if (ImGui::CollapsingHeader(section.name.c_str()))
            {
                section.fnSection();
            }
		}

		ImGui::End();
	}

} // namespace bbzl
