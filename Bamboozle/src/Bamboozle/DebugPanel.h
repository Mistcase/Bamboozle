#pragma once

#include <functional>
#include <string>
#include <vector>

namespace bbzl
{
	class DebugPanel
	{
	public:
		using FnSectionFunc = std::function<void()>;

	public:
		static DebugPanel& Instance()
		{
			static DebugPanel panel;
			return panel;
		}

		void registerSection(const std::string& str, const FnSectionFunc& section);
		void unregisterSection(const std::string& str);

		void render();

	private:
		struct Section
		{
            Section(const std::string& name, const FnSectionFunc& func)
                : name(name)
                , fnSection(func)
            {
            }
            
			std::string name;
			FnSectionFunc fnSection;
		};

		std::vector<Section> m_sections;
	};

} // namespace bbzl
