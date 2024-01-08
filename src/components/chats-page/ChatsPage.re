open Util.Exceptions;

[@react.component]
let make = () => {
  let (chatsState, setChatsState) = React.useState(_ => [||]);

  let loadChats =
    React.useCallback1(
      () => {
        let _ =
          Js.Promise.(
            Fetch.fetchWithInit(
              "/getChatIds",
              Fetch.RequestInit.make(~method_=Get, ~credentials=Include, ()),
            )
            |> then_(response =>
                 switch (Fetch.Response.status(response)) {
                 | 200 => response |> resolve
                 | code => Js.Promise.reject(ResponseCode(code))
                 }
               )
            |> then_(Fetch.Response.json)
            |> then_(json =>
                 json
                 ->Js.Json.decodeArray
                 ->Belt.Option.getExn
                 ->Belt.Array.map(Js.Json.decodeNumber)
                 ->resolve
               )
            |> then_(data => setChatsState(_ => data) |> resolve)
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
      [|setChatsState|],
    );

  React.useEffect0(() => {
    loadChats();
    Some(() => ());
  });

  let chats =
    chatsState
    |> Array.map(num => {
         switch (num) {
         | Some(n) =>
           <input
             className="selfofly-chats-page__button"
             type_="button"
             value={"Chat " ++ (n |> Float.to_int |> Int.to_string)}
             onClick={_ =>
               ReasonReactRouter.push(
                 "/chat/" ++ (n |> Float.to_int |> Int.to_string),
               )
             }
           />
         | None => <div />
         }
       })
    |> React.array;

  <div className="selfofly-chats-page">
    <div className="selfofly-chats-page__main-container"> chats </div>
  </div>;
};
