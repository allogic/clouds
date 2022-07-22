#include <glfw/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include <implot/implot.h>

#include <core/fwd_list.h>
#include <core/fwd_iterator.h>

#include <ui.h>
#include <ecs.h>
#include <profiler.h>

static r32 profiler_history_proc(void* data, i32 index)
{
  profiler_frame_t* history = (profiler_frame_t*)data;
  return history[index].time;
}
static float Sin(void*, int i) { return sinf(i * 0.1f) * 10.0f; }

#ifdef __cplusplus
extern "C" {
#endif

  extern GLFWwindow* window;
  extern profiler_frame_t history[PROFILER_NUM_SAMPLES][PROFILER_NUM_FRAMES];
  extern fwd_list_t entities;

  u8 ui_create()
  {
    u8 status = 0;
    IMGUI_CHECKVERSION();
    ImGuiContext* context_imgui = ImGui::CreateContext();
    ImPlotContext* context_implot = ImPlot::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
      style.WindowRounding = 0.0f;
      style.FrameBorderSize = 0.0f;
      style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
    status |= (u8)(ImGui_ImplGlfw_InitForOpenGL(window, 1) == 0);
    status |= (u8)(ImGui_ImplOpenGL3_Init("#version 460 core") == 0);
    return status;
  }
  void ui_begin()
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
  }
  void ui_end()
  {

  }
  void ui_render()
  {
    glfwMakeContextCurrent(window);
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
  }
  void ui_destroy()
  {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
  }

  void ui_debug_actors(u8* open)
  {
    if ((open != NULL) && (*open == 1))
    {
      ImGui::Begin("Entities", (bool*)open);
      if (ImGui::BeginTable("Entities", 4, ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_RowBg))
      {
        ImGui::TableSetupColumn("addr");
        ImGui::TableSetupColumn("id");
        ImGui::TableSetupColumn("cmask");
        ImGui::TableSetupColumn("pmask");
        ImGui::TableHeadersRow();
        entity_t* entity = NULL;
        fwd_iter_t iter;
        fwd_iter_create(&iter, &entities);
        while (fwd_iter_valid(&iter) == 0)
        {
          entity = (entity_t*)fwd_iter_value(&iter);
          ImGui::TableNextRow(); ImGui::TableNextColumn();
          ImGui::Text("%p", entity); ImGui::TableNextColumn();
          ImGui::Text("%d", entity->id); ImGui::TableNextColumn();
          ImGui::Text("%X", entity->comp_mask); ImGui::TableNextColumn();
          ImGui::Text("%X", entity->proc_mask); ImGui::TableNextColumn();
          fwd_iter_next(&iter);
        }
        ImGui::EndTable();
      }
      ImGui::End();
    }
  }
  void ui_debug_profiler(u8* open)
  {
    if ((open != NULL) && (*open == 1))
    {
      ImGui::Begin("Profiler", (bool*)open);
      ImGui::PushItemWidth(-1.0f);

      static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels;

      if (ImPlot::BeginPlot("##Scrolling", ImVec2(-1, 150))) {
        ImPlot::SetupAxes(NULL, NULL, flags, flags);
        ImPlot::SetupAxisLimits(ImAxis_X1, 0.0f, 1.0f, ImGuiCond_Always);
        ImPlot::SetupAxisLimits(ImAxis_Y1, 0.0f, 1.0f);
        ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 0.5f);
        static u32 offset = 0;
        ImPlot::PlotShaded("Mouse X", &history[0]->time_delta, PROFILER_NUM_SAMPLES, 0.0f, 1.0f, 0, 0, (offset++ % PROFILER_NUM_SAMPLES), sizeof(profiler_frame_t) * PROFILER_NUM_FRAMES);
        //ImPlot::PlotLine("Mouse Y", &sdata2.Data[0].x, &sdata2.Data[0].y, sdata2.Data.size(), 0, sdata2.Offset, 2 * sizeof(float));
        ImPlot::EndPlot();
      }
      //if (ImPlot::BeginPlot("##Rolling", ImVec2(-1, 150))) {
      //  ImPlot::SetupAxes(NULL, NULL, flags, flags);
      //  ImPlot::SetupAxisLimits(ImAxis_X1, 0, history, ImGuiCond_Always);
      //  ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 1);
      //  ImPlot::PlotLine("Mouse X", &rdata1.Data[0].x, &rdata1.Data[0].y, rdata1.Data.size(), 0, 0, 2 * sizeof(float));
      //  ImPlot::PlotLine("Mouse Y", &rdata2.Data[0].x, &rdata2.Data[0].y, rdata2.Data.size(), 0, 0, 2 * sizeof(float));
      //  ImPlot::EndPlot();
      //}

      //ImGui::PlotHistogram("", profiler_history_proc, history, PROFILER_NUM_SAMPLES, 0, "History", 0.0f, 20.0f, ImVec2{ 0.0f, 150.0f });
      ImGui::PopItemWidth();
      ImGui::End();
    }
  }

#ifdef __cplusplus
}
#endif