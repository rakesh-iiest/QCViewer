#ifndef CIRCUITWIDGET__INCLUDED
#define CIRCUITWIDGET__INCLUDED

#include <gtkmm/drawingarea.h>
#include <circuit.h>
#include <string>
#include "draw.h"
#include <state.h>

class CircuitWidget : public Gtk::DrawingArea {
public:
  CircuitWidget ();
  virtual ~CircuitWidget ();
  void load (string);
  void loadArch (string);

  void set_window (Gtk::Window *);
  void set_offset (int);
  void set_drawarch (bool);
  void set_drawparallel (bool);

  void savepng (std::string);
  void savesvg (std::string);

  void set_scale (double);
  double get_scale ();
  int get_QCost ();
  int get_Depth ();
  int get_NumGates ();

  void set_state (State*);
  bool step ();
  bool run (bool);
  void reset ();
  void insert_gate_in_new_column (Gate *, unsigned int);
  void insert_gate_in_column (Gate *, unsigned int);
  void insert_gate_at_front (Gate*);
  void delete_gate (unsigned int);
  void set_insert (bool);
  void set_selection (int);
  void generate_layout_rects ();
  void toggle_breakpoint_edit ();
protected:
  //Override default signal handler:
  virtual bool on_expose_event(GdkEventExpose* event);
  virtual bool on_button_release_event(GdkEventButton* event);
  virtual bool onScrollEvent (GdkEventScroll* event);
  virtual bool onMotionEvent (GdkEventMotion* event);
  virtual bool on_button_press_event(GdkEventButton* event);
  virtual void on_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context,
      int x, int y, const Gtk::SelectionData& selection_data, guint info, guint time);

private:
  vector<LayoutColumn> layout;
  vector<unsigned int> breakpoints;

  bool breakpointmode;
  bool simulation_enabled;
  unsigned int NextGateToSimulate;
  bool insert;
  bool panning;
  double oldmousex, oldmousey;

  void toggle_selection (int);

  State *state;
  bool drawarch, drawparallel;
  Gtk::Window *win;
  int yoffset;
  Circuit *circuit;
  cairo_rectangle_t ext;
  double wirestart, wireend;
  void force_redraw ();

  double scale;
  double cx, cy;

  vector<gateRect> columns;
  vector<gateRect> rects;
  int selection;


  unsigned int getFirstWire (double);
};

#endif