/////////////////////////////////////////////////////////////////////////////
// Name:        scrolwin.h
// Purpose:     interface of wxScrolledWindow
// Author:      wxWidgets team
// RCS-ID:      $Id$
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

/**
    @wxheader{scrolwin.h}

    The wxScrolled<T> class manages scrolling for its client area, transforming
    the coordinates according to the scrollbar positions, and setting the
    scroll positions, thumb sizes and ranges according to the area in view.

    There are two commonly used (but not the only possible!) specializations of
    this class:

    - ::wxScrolledWindow, aka wxScrolled<wxPanel>, is equivalent to
      ::wxScrolledWindow from earlier versions. Derived from wxPanel, it shares
      wxPanel's behaviour with regard to TAB traversal and focus handling. Use
      this if the scrolled window will have children controls.

    - ::wxScrolledCanvas, aka wxScrolled<wxWindow>, derives from wxWindow and
      so doesn't handle children specially. This is suitable e.g. for
      implementating scrollable controls such as tree or list controls.

    Starting from version 2.4 of wxWidgets, there are several ways to use a
    wxScrolled<T>. In particular, there are now three ways to set the
    size of the scrolling area:

    One way is to set the scrollbars directly using a call to SetScrollbars().
    This is the way it used to be in any previous version of wxWidgets and it
    will be kept for backwards compatibility.

    An additional method of manual control, which requires a little less
    computation of your own, is to set the total size of the scrolling area by
    calling either wxWindow::SetVirtualSize(), or wxWindow::FitInside(), and
    setting the scrolling increments for it by calling SetScrollRate().
    Scrolling in some orientation is enabled by setting a non-zero increment
    for it.

    The most automatic and newest way is to simply let sizers determine the
    scrolling area. This is now the default when you set an interior sizer into
    a wxScrolled<T> with wxWindow::SetSizer().  The scrolling area will be
    set to the size requested by the sizer and the scrollbars will be assigned
    for each orientation according to the need for them and the scrolling
    increment set by SetScrollRate().  As above, scrolling is only enabled in
    orientations with a non-zero increment.  You can influence the minimum size
    of the scrolled area controlled by a sizer by calling
    wxWindow::SetVirtualSizeHints(). (Calling SetScrollbars() has analogous
    effects in wxWidgets 2.4 -- in later versions it may not continue to
    override the sizer.)

    Note that if maximum size hints are still supported by
    wxWindow::SetVirtualSizeHints(), use them at your own dire risk. They may
    or may not have been removed for 2.4, but it really only makes sense to set
    minimum size hints here.  We should probably replace
    wxWindow::SetVirtualSizeHints() with wxWindow::SetMinVirtualSize() or
    similar and remove it entirely in future.

    As with all windows, an application can draw onto a wxScrolled<T> using
    a @ref overview_dcoverview "device context".

    You have the option of handling the OnPaint handler or overriding the
    wxScrolled<T>::OnDraw() function, which is passed a pre-scrolled device
    context (prepared by wxScrolled<T>::DoPrepareDC()).

    If you don't wish to calculate your own scrolling, you must call
    DoPrepareDC() when not drawing from within OnDraw(), to set the device
    origin for the device context according to the current scroll position.

    A wxScrolled<T> will normally scroll itself and therefore its child windows
    as well. It might however be desired to scroll a different window than
    itself: e.g. when designing a spreadsheet, you will normally only have to
    scroll the (usually white) cell area, whereas the (usually grey) label area
    will scroll very differently. For this special purpose, you can call
    SetTargetWindow() which means that pressing the scrollbars will scroll a
    different window.

    Note that the underlying system knows nothing about scrolling coordinates,
    so that all system functions (mouse events, expose events, refresh calls
    etc) as well as the position of subwindows are relative to the "physical"
    origin of the scrolled window. If the user insert a child window at
    position (10,10) and scrolls the window down 100 pixels (moving the child
    window out of the visible area), the child window will report a position
    of (10,-90).

    @beginStyleTable
    @style{wxRETAINED}:
           Uses a backing pixmap to speed refreshes. Motif only.
    @endStyleTable

    @remarks
    Use wxScrolled<T> for applications where the user scrolls by a fixed
    amount, and where a 'page' can be interpreted to be the current visible
    portion of the window. For more sophisticated applications, use the
    wxScrolled<T> implementation as a guide to build your own scroll
    behaviour or use wxVScrolledWindow or its variants.

    @since wxScrolled<T> template exists since version 2.9.0. In older
           versions, only ::wxScrolledWindow (equivalent of wxScrolled<wxPanel>)
           was available.

    @library{wxcore}
    @category{miscwnd}

    @see wxScrollBar, wxClientDC, wxPaintDC,
         wxVScrolledWindow, wxHScrolledWindow, wxHVScrolledWindow,
*/
template<class T>
class wxScrolled : public T
{
public:
    /// Default constructor.
    wxScrolled();

    /**
        Constructor.

        @param parent
            Parent window.
        @param id
            Window identifier. The value @c wxID_ANY indicates a default value.
        @param pos
            Window position. If a position of @c wxDefaultPosition is specified
            then a default position is chosen.
        @param size
            Window size. If a size of @c wxDefaultSize is specified then the
            window is sized appropriately.
        @param style
            Window style. See wxScrolled<T>.
        @param name
            Window name.

        @remarks The window is initially created without visible scrollbars.
                 Call SetScrollbars() to specify how big the virtual window
                 size should be.
    */
    wxScrolled(wxWindow* parent, wxWindowID id = -1,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = wxHSCROLL | wxVSCROLL,
               const wxString& name = "scrolledWindow");


    /**
        Translates the logical coordinates to the device ones. For example, if
        a window is scrolled 10 pixels to the bottom, the device coordinates of
        the origin are (0, 0) (as always), but the logical coordinates are (0,
        10) and so the call to CalcScrolledPosition(0, 10, xx, yy) will return
        0 in yy.

        @see CalcUnscrolledPosition()
    */
    void CalcScrolledPosition(int x, int y, int* xx, int* yy) const;

    /**
        Translates the device coordinates to the logical ones. For example, if
        a window is scrolled 10 pixels to the bottom, the device coordinates of
        the origin are (0, 0) (as always), but the logical coordinates are (0,
        10) and so the call to CalcUnscrolledPosition(0, 0, xx, yy) will return
        10 in yy.

        @see CalcScrolledPosition()
    */
    void CalcUnscrolledPosition(int x, int y, int* xx, int* yy) const;

    /**
        Creates the window for two-step construction. Derived classes
        should call or replace this function. See wxScrolled<T> constructor
        for details.
    */
    bool Create(wxWindow* parent, wxWindowID id = -1,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = wxHSCROLL | wxVSCROLL,
                const wxString& name = "scrolledWindow");

    /**
        Call this function to prepare the device context for drawing a scrolled
        image.

        It sets the device origin according to the current scroll position.
        DoPrepareDC() is called automatically within the default OnPaint()
        event handler, so your OnDraw() override will be passed a
        'pre-scrolled' device context. However, if you wish to draw from
        outside of OnDraw() (via OnPaint()), or you wish to implement OnPaint()
        yourself, you must call this function yourself.

        For example:
        @code
        void MyWindow::OnEvent(wxMouseEvent& event)
        {
          wxClientDC dc(this);
          DoPrepareDC(dc);

          dc.SetPen(*wxBLACK_PEN);
          float x, y;
          event.Position(&x, &y);
          if (xpos > -1 && ypos > -1 && event.Dragging())
          {
            dc.DrawLine(xpos, ypos, x, y);
          }
          xpos = x;
          ypos = y;
        }
        @endcode

    */
    void DoPrepareDC(wxDC& dc);

    /**
        Enable or disable physical scrolling in the given direction. Physical
        scrolling is the physical transfer of bits up or down the
        screen when a scroll event occurs. If the application scrolls by a
        variable amount (e.g. if there are different font sizes) then physical
        scrolling will not work, and you should switch it off. Note that you
        will have to reposition child windows yourself, if physical scrolling
        is disabled.

        @param xScrolling
            If @true, enables physical scrolling in the x direction.
        @param yScrolling
            If @true, enables physical scrolling in the y direction.

        @remarks Physical scrolling may not be available on all platforms. Where
                 it is available, it is enabled by default.
    */
    void EnableScrolling(bool xScrolling, bool yScrolling);

    /**
        Get the number of pixels per scroll unit (line), in each direction, as
        set by SetScrollbars(). A value of zero indicates no scrolling in that
        direction.

        @param xUnit
            Receives the number of pixels per horizontal unit.
        @param yUnit
            Receives the number of pixels per vertical unit.

        @see SetScrollbars(), GetVirtualSize()
    */
    void GetScrollPixelsPerUnit(int* xUnit, int* yUnit) const;

    /**
        Get the position at which the visible portion of the window starts.

        @param x
            Receives the first visible x position in scroll units.
        @param y
            Receives the first visible y position in scroll units.

        @remarks If either of the scrollbars is not at the home position, x
                 and/or y will be greater than zero.  Combined with
                 wxWindow::GetClientSize(), the application can use this
                 function to efficiently redraw only the visible portion
                 of the window.  The positions are in logical scroll
                 units, not pixels, so to convert to pixels you will
                 have to multiply by the number of pixels per scroll
                 increment.

        @see SetScrollbars()
    */
    void GetViewStart(int* x, int* y) const;

    /**
        Gets the size in device units of the scrollable window area (as
        opposed to the client size, which is the area of the window currently
        visible).

        @param x
            Receives the length of the scrollable window, in pixels.
        @param y
            Receives the height of the scrollable window, in pixels.

        @remarks Use wxDC::DeviceToLogicalX() and wxDC::DeviceToLogicalY() to
                 translate these units to logical units.

        @see SetScrollbars(), GetScrollPixelsPerUnit()
    */
    void GetVirtualSize(int* x, int* y) const;

    /**
        Motif only: @true if the window has a backing bitmap.
    */
    bool IsRetained() const;

    /**
        Called by the default paint event handler to allow the application to
        define painting behaviour without having to worry about calling
        DoPrepareDC().

        Instead of overriding this function you may also just process the paint
        event in the derived class as usual, but then you will have to call
        DoPrepareDC() yourself.
    */
    virtual void OnDraw(wxDC& dc);

    /**
        This function is for backwards compatibility only and simply calls
        DoPrepareDC() now. Notice that it is not called by the default paint
        event handle (DoPrepareDC() is), so overriding this method in your
        derived class is useless.
    */
    void PrepareDC(wxDC& dc);

    /**
        Scrolls a window so the view start is at the given point.

        @param x
            The x position to scroll to, in scroll units.
        @param y
            The y position to scroll to, in scroll units.

        @remarks The positions are in scroll units, not pixels, so to convert to
                 pixels you will have to multiply by the number of
                 pixels per scroll increment. If either parameter is -1,
                 that position will be ignored (no change in that
                 direction).

        @see SetScrollbars(), GetScrollPixelsPerUnit()
    */
    void Scroll(int x, int y);

    /**
        Set the horizontal and vertical scrolling increment only. See the
        pixelsPerUnit parameter in SetScrollbars().
    */
    void SetScrollRate(int xstep, int ystep);

    /**
        Sets up vertical and/or horizontal scrollbars.

        The first pair of parameters give the number of pixels per 'scroll
        step', i.e. amount moved when the up or down scroll arrows are pressed.
        The second pair gives the length of scrollbar in scroll steps, which
        sets the size of the virtual window.

        @a xPos and @a yPos optionally specify a position to scroll to
        immediately.

        For example, the following gives a window horizontal and vertical
        scrollbars with 20 pixels per scroll step, and a size of 50 steps (1000
        pixels) in each direction:
        @code
        window->SetScrollbars(20, 20, 50, 50);
        @endcode

        wxScrolled<T> manages the page size itself, using the current client
        window size as the page size.

        Note that for more sophisticated scrolling applications, for example
        where scroll steps may be variable according to the position in the
        document, it will be necessary to derive a new class from wxWindow,
        overriding OnSize() and adjusting the scrollbars appropriately.

        @param pixelsPerUnitX
            Pixels per scroll unit in the horizontal direction.
        @param pixelsPerUnitY
            Pixels per scroll unit in the vertical direction.
        @param noUnitsX
            Number of units in the horizontal direction.
        @param noUnitsY
            Number of units in the vertical direction.
        @param xPos
            Position to initialize the scrollbars in the horizontal direction,
            in scroll units.
        @param yPos
            Position to initialize the scrollbars in the vertical direction, in
            scroll units.
        @param noRefresh
            Will not refresh window if @true.

        @see wxWindow::SetVirtualSize()
    */
    void SetScrollbars(int pixelsPerUnitX, int pixelsPerUnitY,
                       int noUnitsX,
                       int noUnitsY,
                       int xPos = 0,
                       int yPos = 0,
                       bool noRefresh = false);

    /**
        Call this function to tell wxScrolled to perform the actual
        scrolling on a different window (and not on itself).
    */
    void SetTargetWindow(wxWindow* window);
};


/**
    Scrolled window derived from wxPanel.

    See wxScrolled<T> for detailed description.

    @note Note that because this class derives from wxPanel, it shares its
          behavior with regard to TAB traversal and focus handling (in
          particular, it forwards focus to its children). If you don't want
          this behaviour, use ::wxScrolledCanvas instead.

    @note wxScrolledWindow is an alias for wxScrolled<wxPanel> since version
          2.9.0. In older versions, it was a standalone class.

    @library{wxcore}
    @category{miscwnd}

    @see wxScrolled, wxScrolledCanvas
*/
typedef wxScrolled<wxPanel> wxScrolledWindow;

/**
    Alias for wxScrolled<wxWindow>. Scrolled window that doesn't have children
    and so doesn't need or want special handling of TAB traversal.

    @since 2.9.0

    @library{wxcore}
    @category{miscwnd}

    @see wxScrolled, ::wxScrolledWindow
*/
typedef wxScrolled<wxWindow> wxScrolledCanvas;
