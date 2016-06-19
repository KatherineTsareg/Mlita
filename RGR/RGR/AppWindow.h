#pragma once
#include "stdafx.h"
#include "AppMenu.h"
#include "ConvexHull.h"

class CAppWindow : public sf::RenderWindow
{
public:
    CAppWindow();
    ~CAppWindow();

    void EnterLoop();

private:
    enum class State
    {
        WaitingInput,
        RunningDemo,
        WaitingOutput,
    };

    void SetState(State state);
    void AskOpenInput();
    void AskSaveOutput();

	void Draw();
	void InitializeText();

	void RunAlgorithm();
	void WriteToFile(std::ofstream & fout);
	
	void SetCenter();
	sf::View m_view;

	State m_state = State::WaitingInput;
    std::deque<std::string> m_pendingFramePaths;
    sf::Font m_font;
	sf::Font m_fontForText;
    sf::Texture m_activeFrame;
    std::unique_ptr<CAppMenu> m_menu;
    size_t m_openActionId = 0;
    size_t m_saveActionId = 0;
	
	std::shared_ptr<CConvexHull> m_convexHull;
	bool m_hasConvexHull = false;
	sf::Text m_text;
};
