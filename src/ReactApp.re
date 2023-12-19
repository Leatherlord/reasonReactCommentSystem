module App = {
  [@react.component]
  let make = () => {
    let url = ReasonReactRouter.useUrl();
    switch (url.path) {
    | ["main"] => <ChatsPage />
    | ["chat", id] => <CommentPage chatId=id />
    | ["error", code] => <ErrorPage errorCode=code />
    | ["auth"] => <AuthorizationPage />
    | _ =>
      ReasonReactRouter.push("auth");
      <AuthorizationPage />;
    };
  };
};

ReactDOM.querySelector("#root")
->(
    fun
    | Some(root) => ReactDOM.render(<App />, root)
    | None =>
      Js.Console.error(
        "Failed to start React: couldn't find the #root element",
      )
  );
