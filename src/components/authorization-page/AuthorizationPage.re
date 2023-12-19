open Util.Exceptions;

[@react.component]
let make = () => {
  let (login, setLogin) = React.useState(_ => "");
  let (password, setPassword) = React.useState(_ => "");

  let onAuth =
    React.useCallback2(
      () => {
        let payload = Js.Dict.empty();
        Js.Dict.set(payload, "username", Js.Json.string(login));
        Js.Dict.set(payload, "password", Js.Json.string(password));
        let _ =
          Js.Promise.(
            Fetch.fetchWithInit(
              "http://localhost:8080/login",
              Fetch.RequestInit.make(
                ~method_=Post,
                ~body=
                  Fetch.BodyInit.make(
                    Js.Json.stringify(Js.Json.object_(payload)),
                  ),
                ~headers=
                  Fetch.HeadersInit.make({
                    "Content-Type": "application/json",
                  }),
                ~credentials=Include,
                (),
              ),
            )
            |> then_(response =>
                 switch (Fetch.Response.status(response)) {
                 | 200 => ReasonReactRouter.push("main") |> resolve
                 | code => Js.Promise.reject(ResponseCode(code))
                 }
               )
            |> catch(error =>
                 {
                   switch (Obj.magic(error)) {
                   | ResponseCode(code) =>
                     ReasonReactRouter.push("/error/" ++ Int.to_string(code))
                   | _ => ReasonReactRouter.push("/error/UnknownError")
                   };
                 }
                 |> resolve
               )
          );
        ();
      },
      (login, password),
    );

  let onRegistration =
    React.useCallback2(
      () => {
        let payload = Js.Dict.empty();
        Js.Dict.set(payload, "username", Js.Json.string(login));
        Js.Dict.set(payload, "password", Js.Json.string(password));
        let _ =
          Js.Promise.(
            Fetch.fetchWithInit(
              "http://localhost:8080/registration",
              Fetch.RequestInit.make(
                ~method_=Post,
                ~body=
                  Fetch.BodyInit.make(
                    Js.Json.stringify(Js.Json.object_(payload)),
                  ),
                ~headers=
                  Fetch.HeadersInit.make({
                    "Content-Type": "application/json",
                  }),
                ~credentials=Include,
                (),
              ),
            )
            |> then_(response =>
                 switch (Fetch.Response.status(response)) {
                 | 200 => onAuth() |> resolve
                 | code => Js.Promise.reject(ResponseCode(code))
                 }
               )
            |> catch(error =>
                 {
                   switch (Obj.magic(error)) {
                   | ResponseCode(code) =>
                     ReasonReactRouter.push("/error/" ++ Int.to_string(code))
                   | _ => ReasonReactRouter.push("/error/UnknownError")
                   };
                 }
                 |> resolve
               )
          );
        ();
      },
      (login, password),
    );

  <div className="selfofly-authorization-page">
    <div className="selfofly-authorization-page__main-container">
      <input
        placeholder="Login"
        className="selfofly-authorization-page__input"
        value=login
        onChange={e => setLogin(_ => e->ReactEvent.Form.target##value)}
      />
      <input
        placeholder="Password"
        type_="password"
        className="selfofly-authorization-page__input"
        value=password
        onChange={e => setPassword(_ => e->ReactEvent.Form.target##value)}
      />
      <input
        className="selfofly-authorization-page__button"
        type_="button"
        value="Authorization"
        onClick={_ => onAuth()}
      />
      <input
        type_="button"
        value="Registration"
        className="selfofly-authorization-page__button"
        onClick={_ => onRegistration()}
      />
    </div>
  </div>;
};
