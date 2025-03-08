#include "ThrashTheCacheComponent.h"
#include <imgui.h>
#include <imgui_plot.h>
#include <vector>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <map>
#include <iostream>

dae::ThrashTheCacheComponent::ThrashTheCacheComponent(GameObject* pOwner)
    :Component{pOwner}
{
}

void dae::ThrashTheCacheComponent::Render() 
{
    Ex1();
    Ex2();
}

void dae::ThrashTheCacheComponent::Update(float )
{
}

void dae::ThrashTheCacheComponent::FixedUpdate()
{
}

void dae::ThrashTheCacheComponent::Ex1()
{
    //std::cout << "Ex1() is being called!\n";
    bool windowActive{true};
    static bool clickedBtn{};
    static bool isCalculated{};

    //ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver);
    //ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_FirstUseEver);

    ImGui::Begin("Exercise 1", &windowActive, ImGuiWindowFlags_AlwaysAutoResize);

    static int sample = 20;
    ImGui::InputInt("# Samples", &sample);

    ImGui::PlotConfig conf;
    conf.scale.min = 0;
    conf.tooltip.show = true;
    conf.tooltip.format = "Stepsize:%.0f\nValue: %.1f";
    conf.grid_x.show = false;
    conf.grid_y.show = true;
    conf.frame_size = ImVec2(200, 100);
    conf.line_thickness = 2.0f;

    if (ImGui::Button("Thrash the Cache"))
    {
        ImGui::Text("Wait for it...");
        clickedBtn = true;
    }

    if (clickedBtn)
    {
        Ex1Calc(sample);
        isCalculated = true;
        clickedBtn = false;
    }
    if (isCalculated)
    {
        conf.values.color = ImColor(255, 165, 0); //orange
        conf.values.xs = m_Ex1XData.data();
        conf.values.ys = m_Ex1YData.data();
        conf.values.count = static_cast<int>(m_Ex1XData.size()+1);
        conf.scale.max = *std::max_element(m_Ex1YData.begin(), m_Ex1YData.end());;
        ImGui::Plot("Exercise 1", conf);

    }
    ImGui::End();
}

void dae::ThrashTheCacheComponent::Ex2()
{
    bool windowActive{ true };

    static bool clickedBtn{};
    static bool isCalculating{};

    static bool clickedBtnAlt{};
    static bool isCalculatingAlt{};

    static int sample = 20;
    ImGui::Begin("Exercise 2", &windowActive, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::InputInt("# Samples", &sample);

    ImGui::PlotConfig conf;
    conf.scale.min = 0;
    conf.tooltip.show = true;
    conf.tooltip.format = "Stepsize:%.0f\nValue: %.1f";
    conf.grid_x.show = false;
    conf.grid_y.show = true;
    conf.frame_size = ImVec2(200, 100);
    conf.line_thickness = 2.0f;

    if (ImGui::Button("Thrash the Cache with GameObject3D"))
    {
        ImGui::Text("Wait for it...");
        clickedBtn = true;
    }
    if (clickedBtn)
    {
       
        Ex2Calc(sample);
        isCalculating = true;
        clickedBtn = false;
    }
    if (isCalculating)
    {
        conf.values.color = ImColor(0, 255, 0); //green
        conf.values.xs = m_Ex2XData.data();
        conf.values.ys = m_Ex2YData.data();
        conf.values.count = static_cast<int>(m_Ex2XData.size()+1);
        conf.scale.max = *std::max_element(m_Ex2YData.begin(), m_Ex2YData.end());
        ImGui::Plot("Exercise 2", conf);
    }
    if (ImGui::Button("Thrash the Cache with GameObject3DAlt"))
    {
        clickedBtnAlt = true;
        Ex2AltCalc(sample);
        isCalculatingAlt = true;
        clickedBtnAlt = false;
    }
    if (clickedBtnAlt)
    {
        ImGui::Text("Wait for it...");
    }
    if (isCalculatingAlt)
    {
        conf.values.color = ImColor(0, 0, 255); //blue
        conf.values.xs = m_Ex2XAltData.data();
        conf.values.ys = m_Ex2YAltData.data();
        conf.values.count = static_cast<int>(m_Ex2XAltData.size()+1);
        conf.scale.max = *std::max_element(m_Ex2YAltData.begin(), m_Ex2YAltData.end());
        ImGui::Plot("Exercise 2 Alt", conf);
    }
    if (isCalculatingAlt && isCalculating)
    {
        static const float* y_data[] = { m_Ex2YData.data(), m_Ex2YAltData.data() };
        static ImU32 colors[2] = { ImColor(0, 255, 0), ImColor(0, 0, 255) };

        ImGui::Text("Combined:");
        conf.values.xs = m_Ex2XAltData.data();
        conf.values.count = static_cast<int>(m_Ex2XAltData.size()+1);
        conf.values.ys = nullptr; 
        conf.values.ys_list = y_data;
        conf.values.ys_count = 2;
        conf.values.colors = colors;
        float maxYNormal = *std::max_element(m_Ex2YData.begin(), m_Ex2YData.end());
        float maxYAlt = *std::max_element(m_Ex2YAltData.begin(), m_Ex2YAltData.end());
        conf.scale.max = std::max(maxYNormal, maxYAlt) * 1.1f; //Add 10% padding
        ImGui::Plot("Combined Plot", conf);
    }
    ImGui::End();
}

void dae::ThrashTheCacheComponent::Ex1Calc(int sampleSize)
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

        
        float sum = 0.0f;
        for (float t : timings) sum += t;
        float avgTime = sum / timings.size();
        m_Ex1YData.push_back(avgTime);
        //std::cout << stepsize << ";     " << avgTime << "\n";

    }

    delete[] arr;
}

void dae::ThrashTheCacheComponent::Ex2Calc(int sampleSize )
{
    m_Ex2XData.clear();
    m_Ex2YData.clear();

    const int size = 1 << 20;
    GameObject3D* arr = new GameObject3D[size]();
    
    //std::cout << "size " << size << std::endl;

    //std::cout << "StepSize, AvgTime(ms)\n";

    for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
    {
        m_Ex2XData.push_back(static_cast<float>(stepsize));

        //std::cout << m_ExXData.back() << std::endl;

        std::vector<float> timings;

        for (int sample = 0; sample < sampleSize; sample++)
        {
            auto start = std::chrono::high_resolution_clock::now();

            for (int i = 0; i < size; i += stepsize)
            {
                arr[i].id *= 2;
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
        m_Ex2YData.push_back(avgTime);
        //std::cout << stepsize << ";     " << avgTime << "\n";

    }

    delete[] arr;
}

void dae::ThrashTheCacheComponent::Ex2AltCalc(int sampleSize )
{
    m_Ex2XAltData.clear();
    m_Ex2YAltData.clear();

    const int size = 1 << 20;
    GameObject3DALT* arr = new GameObject3DALT[size]();

    //std::cout << "size " << size << std::endl;

    //std::cout << "StepSize, AvgTime(ms)\n";

    for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
    {
        m_Ex2XAltData.push_back(static_cast<float>(stepsize));

        //std::cout << m_ExXData.back() << std::endl;

        std::vector<float> timings;

        for (int sample = 0; sample < sampleSize; sample++)
        {
            auto start = std::chrono::high_resolution_clock::now();

            for (int i = 0; i < size; i += stepsize)
            {
                arr[i].id *= 2;
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
        m_Ex2YAltData.push_back(avgTime);
        //std::cout << stepsize << ";     " << avgTime << "\n";

    }

    delete[] arr;
}
