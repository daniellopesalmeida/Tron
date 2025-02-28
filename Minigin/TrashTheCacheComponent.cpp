#include "TrashTheCacheComponent.h"
#include <imgui.h>
#include <imgui_plot.h>
#include <vector>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <map>
#include <iostream>

dae::TrashTheCacheComponent::TrashTheCacheComponent(GameObject* pOwner)
    :Component{pOwner}
{
}

void dae::TrashTheCacheComponent::Render() 
{
    Ex1();
    Ex2();
}

void dae::TrashTheCacheComponent::Update(float )
{
}

void dae::TrashTheCacheComponent::FixedUpdate()
{
}

void dae::TrashTheCacheComponent::Ex1()
{
    //std::cout << "Ex1() is being called!\n";
    bool windowActive{true};
    static bool clickedBtn{};
    static bool isCalculated{};

    //ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver);
    //ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_FirstUseEver);

    ImGui::Begin("Exercise 1", &windowActive, ImGuiWindowFlags_AlwaysAutoResize);

    static int sample = 10;
    ImGui::InputInt("# Samples", &sample);

    ImGui::PlotConfig conf;
    conf.scale.min = 0;
    conf.tooltip.show = true;
    conf.tooltip.format = "Stepsize:%.0f\nValue: %.0f";
    conf.grid_x.show = false;
    conf.grid_y.show = false;
    conf.frame_size = ImVec2(200, 100);
    conf.line_thickness = 2.0f;

    if (ImGui::Button("Trash the Cache"))
    {
        clickedBtn = true;
    }

    if (clickedBtn)
    {
        ImGui::Text("Wait for it...");
        Ex1Calc(sample);
        isCalculated = true;
        clickedBtn = false;
    }
    if (isCalculated)
    {
        conf.values.color = ImColor(255, 165, 0);
        conf.values.xs = m_Ex1XData.data();
        conf.values.ys = m_Ex1YData.data();
        conf.values.count = static_cast<int>(m_Ex1XData.size()+1);
        conf.scale.max = 1024;
        ImGui::Plot("Exercise 1", conf);
    }
    ImGui::End();
}

void dae::TrashTheCacheComponent::Ex2()
{
    bool windowActive{ true };

    static bool clickedBtn{};
    static bool isCalculating{};

    static bool clickedBtnAlt{};
    static bool isCalculatingAlt{};

    static int sample = 10;
    ImGui::Begin("Exercise 2", &windowActive, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::InputInt("# Samples", &sample);


    ImGui::End();
}

void dae::TrashTheCacheComponent::Ex2Alt()
{
}

void dae::TrashTheCacheComponent::Ex1Calc(int sampleSize)
{
    m_Ex1XData.clear();
    m_Ex1YData.clear();


    const int size = 1 << 20;
    int* arr = new int[size](0);
    //std::vector<int> arr(size, 0);
    //std::cout << "size " << size << std::endl;

    //std::cout << "StepSize, AvgTime(ms)\n";

    for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
    {
        m_Ex1XData.push_back(static_cast<float>(stepsize));

        //std::cout << m_ExXData.back() << std::endl;

        std::vector<float> timings;

        for (int sample = 0; sample < sampleSize; sample++)
        {
            auto start = std::chrono::high_resolution_clock::now();

            for (int i = 0; i < size; i += stepsize)
            {
                arr[i] *= 2;
            }

            auto end = std::chrono::high_resolution_clock::now();
            float elapsedTime = static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());

            timings.push_back(elapsedTime);
        }

        std::sort(timings.begin(), timings.end());
        timings.erase(timings.begin());
        timings.pop_back(); 

        
        float sum = 0.0;
        for (float t : timings) sum += t;
        float avgTime = sum / timings.size();
        m_Ex1YData.push_back(avgTime);
        //std::cout << stepsize << ";     " << avgTime << "\n";

    }

    delete[] arr;
}

void dae::TrashTheCacheComponent::Ex2Calc(int )
{
}
