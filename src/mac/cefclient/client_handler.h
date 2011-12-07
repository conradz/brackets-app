// Copyright (c) 2011 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef _CLIENT_HANDLER_H
#define _CLIENT_HANDLER_H

#include "include/cef.h"
#include "download_handler.h"
#include "util.h"


// Define this value to redirect all popup URLs to the main application browser
// window.
//#define TEST_REDIRECT_POPUP_URLS


// ClientHandler implementation.
class ClientHandler : public CefClient,
                      public CefLifeSpanHandler,
                      public CefLoadHandler,
                      public CefRequestHandler,
                      public CefDisplayHandler,
                      public CefFocusHandler,
                      public CefKeyboardHandler,
                      public CefPrintHandler,
                      public CefJSBindingHandler,
                      public CefJSDialogHandler,
                      public CefDragHandler,
                      public DownloadListener
{
public:
  ClientHandler();
  virtual ~ClientHandler();

  // CefClient methods
  virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE
      { return this; }
  virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE
      { return this; }
  virtual CefRefPtr<CefRequestHandler> GetRequestHandler() OVERRIDE
      { return this; }
  virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE
      { return this; }
  virtual CefRefPtr<CefFocusHandler> GetFocusHandler() OVERRIDE
      { return this; }
  virtual CefRefPtr<CefKeyboardHandler> GetKeyboardHandler() OVERRIDE
      { return this; }
  virtual CefRefPtr<CefPrintHandler> GetPrintHandler() OVERRIDE
      { return this; }
  virtual CefRefPtr<CefJSBindingHandler> GetJSBindingHandler() OVERRIDE
      { return this; }
  virtual CefRefPtr<CefDragHandler> GetDragHandler() OVERRIDE
      { return this; }

  // CefLifeSpanHandler methods
  virtual bool OnBeforePopup(CefRefPtr<CefBrowser> parentBrowser,
                             const CefPopupFeatures& popupFeatures,
                             CefWindowInfo& windowInfo,
                             const CefString& url,
                             CefRefPtr<CefClient>& client,
                             CefBrowserSettings& settings) OVERRIDE;
  virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
  virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
  virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

  // CefLoadHandler methods
  virtual void OnLoadStart(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefFrame> frame) OVERRIDE;
  virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser,
                         CefRefPtr<CefFrame> frame,
                         int httpStatusCode) OVERRIDE;
  virtual bool OnLoadError(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefFrame> frame,
                           ErrorCode errorCode,
                           const CefString& failedUrl,
                           CefString& errorText) OVERRIDE;
 
  // CefRequestHandler methods
  virtual bool OnBeforeResourceLoad(CefRefPtr<CefBrowser> browser,
                                   CefRefPtr<CefRequest> request,
                                   CefString& redirectUrl,
                                   CefRefPtr<CefStreamReader>& resourceStream,
                                   CefRefPtr<CefResponse> response,
                                   int loadFlags) OVERRIDE;
  virtual bool GetDownloadHandler(CefRefPtr<CefBrowser> browser,
                                  const CefString& mimeType,
                                  const CefString& fileName,
                                  int64 contentLength,
                                  CefRefPtr<CefDownloadHandler>& handler)
                                  OVERRIDE;

  // CefDisplayHandler methods
  virtual void OnNavStateChange(CefRefPtr<CefBrowser> browser,
                                bool canGoBack,
                                bool canGoForward) OVERRIDE;
  virtual void OnAddressChange(CefRefPtr<CefBrowser> browser,
                               CefRefPtr<CefFrame> frame,
                               const CefString& url) OVERRIDE;
  virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
                             const CefString& title) OVERRIDE;
  virtual bool OnConsoleMessage(CefRefPtr<CefBrowser> browser,
                                const CefString& message,
                                const CefString& source,
                                int line) OVERRIDE;
  
  // CefFocusHandler methods.
  virtual void OnFocusedNodeChanged(CefRefPtr<CefBrowser> browser,
                                    CefRefPtr<CefFrame> frame,
                                    CefRefPtr<CefDOMNode> node) OVERRIDE;

  // CefKeyboardHandler methods.
  virtual bool OnKeyEvent(CefRefPtr<CefBrowser> browser,
                          KeyEventType type,
                          int code,
                          int modifiers,
                          bool isSystemKey,
                          bool isAfterJavaScript) OVERRIDE;

  // CefPrintHandler methods.
  virtual bool GetPrintHeaderFooter(CefRefPtr<CefBrowser> browser,
                                    CefRefPtr<CefFrame> frame,
                                    const CefPrintInfo& printInfo,
                                    const CefString& url,
                                    const CefString& title,
                                    int currentPage,
                                    int maxPages,
                                    CefString& topLeft,
                                    CefString& topCenter,
                                    CefString& topRight,
                                    CefString& bottomLeft,
                                    CefString& bottomCenter,
                                    CefString& bottomRight) OVERRIDE;
  
  // CefJSBindingHandler methods
  virtual void OnJSBinding(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefFrame> frame,
                           CefRefPtr<CefV8Value> object) OVERRIDE;
    
    // CefJSDialogHandler methods
    ///
    // Called  to run a JavaScript alert message. Return false to display the
    // default alert or true if you displayed a custom alert.
    ///
    /*--cef()--*/
    virtual bool OnJSAlert(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefFrame> frame,
                           const CefString& message) OVERRIDE;
    
    ///
    // Called to run a JavaScript confirm request. Return false to display the
    // default alert or true if you displayed a custom alert. If you handled the
    // alert set |retval| to true if the user accepted the confirmation.
    ///
    /*--cef()--*/
    virtual bool OnJSConfirm(CefRefPtr<CefBrowser> browser,
                             CefRefPtr<CefFrame> frame,
                             const CefString& message,
                             bool& retval) OVERRIDE;
    
    ///
    // Called to run a JavaScript prompt request. Return false to display the
    // default prompt or true if you displayed a custom prompt. If you handled
    // the prompt set |retval| to true if the user accepted the prompt and request
    // and |result| to the resulting value.
    ///
    /*--cef()--*/
    virtual bool OnJSPrompt(CefRefPtr<CefBrowser> browser,
                            CefRefPtr<CefFrame> frame,
                            const CefString& message,
                            const CefString& defaultValue,
                            bool& retval,
                            CefString& result) OVERRIDE;

  // CefDragHandler methods.
  virtual bool OnDragStart(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefDragData> dragData,
                           DragOperationsMask mask) OVERRIDE;
  virtual bool OnDragEnter(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefDragData> dragData,
                           DragOperationsMask mask) OVERRIDE;

  // DownloadListener methods
  virtual void NotifyDownloadComplete(const CefString& fileName) OVERRIDE;
  virtual void NotifyDownloadError(const CefString& fileName) OVERRIDE;

  void SetMainHwnd(CefWindowHandle hwnd);
  CefWindowHandle GetMainHwnd() { return m_MainHwnd; }
  void SetEditHwnd(CefWindowHandle hwnd);
  void SetButtonHwnds(CefWindowHandle backHwnd,
                      CefWindowHandle forwardHwnd,
                      CefWindowHandle reloadHwnd,
                      CefWindowHandle stopHwnd);
  
  CefRefPtr<CefBrowser> GetBrowser() { return m_Browser; }
  CefWindowHandle GetBrowserHwnd() { return m_BrowserHwnd; }

  std::string GetLogFile();

  void SetLastDownloadFile(const std::string& fileName);
  std::string GetLastDownloadFile();

  // DOM visitors will be called after the associated path is loaded.
  void AddDOMVisitor(const std::string& path, CefRefPtr<CefDOMVisitor> visitor);
  CefRefPtr<CefDOMVisitor> GetDOMVisitor(const std::string& path);

  // Send a notification to the application. Notifications should not block the
  // caller.
  enum NotificationType
  {
    NOTIFY_CONSOLE_MESSAGE,
    NOTIFY_DOWNLOAD_COMPLETE,
    NOTIFY_DOWNLOAD_ERROR,
  };
  void SendNotification(NotificationType type);
  void CloseMainWindow();

protected:
  void SetLoading(bool isLoading);
  void SetNavState(bool canGoBack, bool canGoForward);

  // The child browser window
  CefRefPtr<CefBrowser> m_Browser;

  // The main frame window handle
  CefWindowHandle m_MainHwnd;

  // The child browser window handle
  CefWindowHandle m_BrowserHwnd;

  // The edit window handle
  CefWindowHandle m_EditHwnd;

  // The button window handles
  CefWindowHandle m_BackHwnd;
  CefWindowHandle m_ForwardHwnd;
  CefWindowHandle m_StopHwnd;
  CefWindowHandle m_ReloadHwnd;

  // Support for logging.
  std::string m_LogFile;

  // Support for downloading files.
  std::string m_LastDownloadFile;

  // Support for DOM visitors.
  typedef std::map<std::string, CefRefPtr<CefDOMVisitor> > DOMVisitorMap;
  DOMVisitorMap m_DOMVisitors;

  // True if a form element currently has focus
  bool m_bFormElementHasFocus;

  // Include the default reference counting implementation.
  IMPLEMENT_REFCOUNTING(ClientHandler);
  // Include the default locking implementation.
  IMPLEMENT_LOCKING(ClientHandler);
};

#endif // _CLIENT_HANDLER_H