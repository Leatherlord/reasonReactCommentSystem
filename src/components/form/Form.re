[@react.component]
let make = (~onSubmit) => {
  let (text, setText) = React.useState(() => "");

  let isSendable =
    React.useMemo1(
      () => String.length(text) <= 1000 && String.length(text) > 0,
      [|text|],
    );

  <div className="selfofly-form">
    <textarea
      className="selfofly-form__input selfofly-form__input--text"
      value=text
      onChange={e => setText(_ => e->ReactEvent.Form.target##value)}
      placeholder="Enter your comment"
    />
    <input
      className="selfofly-form__button"
      type_="button"
      value="Send"
      disabled={!isSendable}
      onClick={_ =>
        if (isSendable) {
          onSubmit(text);
          setText(_ => "");
        }
      }
    />
    <span
      className="selfofly-form__error-message"
      style={ReactDOM.Style.make(~display=isSendable ? "none" : "block", ())}>
      {React.string(
         "Either your name is longer than a 100 chars, or message is longer than a 1000, or their lengths are 0",
       )}
    </span>
  </div>;
};
