# ReasonML + React: Frontend for simple messaging system
## Functional Programming course fourth assignment. 
Simple UI for basic messaging system with multiple chats

# Лабораторная работа №4 по предмету: «Функциональное программирование»

Выполнил:
Бойко В. А.

В рамках данной лабораторной работы мной была реализована простая система чатов на языке ReasonML с использованием React.

Пример кода (страница чата с сообщениями):

```Reason

[@react.component]
let make = (~chatId) => {
  let (commentsState, setCommentsState) = React.useState(_ => [||]);

  let loadComments =
    React.useCallback1(
      () => {
        let _ =
          Js.Promise.(
            Fetch.fetchWithInit(
              "http://localhost:8080/allComments/" ++ chatId,
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
                 ->Belt.Array.map(CommentType.decode)
                 ->resolve
               )
            |> then_(data => setCommentsState(_ => data) |> resolve)
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
      [|setCommentsState|],
    );

  let sendComment =
    React.useCallback1(
      (comment: string) => {
        let payload = Js.Dict.empty();
        Js.Dict.set(payload, "comment", Js.Json.string(comment));
        Js.Dict.set(
          payload,
          "time",
          Js.Date.make() |> Js.Date.toISOString |> Js.Json.string,
        );
        let _ =
          Js.Promise.(
            Fetch.fetchWithInit(
              "http://localhost:8080/addComment/" ++ chatId,
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
            |> then_(_ => loadComments() |> resolve)
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
      [|loadComments|],
    );

  React.useEffect0(() => {
    loadComments();
    let id = Js.Global.setInterval(loadComments, 10000);
    Some(() => Js.Global.clearInterval(id));
  });

  let comments =
    Array.map(
      (comment: CommentType.t) =>
        <Comment
          key={comment.author ++ (comment.time |> Js.Date.toISOString)}
          author={comment.author}
          comment={comment.comment}
          time={comment.time |> Js.Date.toDateString}
        />,
      commentsState,
    )
    |> React.array;

  <div className="selfofly-comments-page">
    <div className="selfofly-comments-page__content-container">
      <CommentsContainer> comments </CommentsContainer>
      <Form onSubmit=sendComment />
    </div>
  </div>;
};

```

# Заключение

Данная работа оказалась не слишком сложной (хотя, безусловно, некоторые трудности вставали передо мной) - вероятнее всего это связано с тем, что React изначально очень тесно связан с функциональным стилем программирования. В самой его основе лежит концепция иммутабельного состояния, что делает интеграцию с функциональным языком программирования практически безболезненной. К тому же в современном мире React в подавляющем большинстве случаев используют совместно с TypeScript и подобными расширениями JS, так что и строгая система типов ReasonML не доставила особых проблем именно с React'ом. Проблемы начали проявляться только в тот момент, когда встала необходимость отправлять запросы на сервер, и, соответственно, использовать Fetch API с его Promise'ами. Я довольно долго разбирался с тем, как авторы библиотеки, осуществляющей связывание этого API с ReasonML, предполагали работу с ними, и даже пришлось обращаться за помощью в тематический Discord-канал, где обитают пользователи этого экзотического языка. В целом, по окончании работы, опыт получился больше положительный, чем нет.