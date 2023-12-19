[@react.component]
let make = (~errorCode) => {
  <div className="selfofly-error-page">
    <div className="selfofly-error-page__main-container">
      <span className="selfofly-error-page__error-code">
        {React.string(errorCode)}
      </span>
      <span className="selfofly-error-page__message">
        {React.string("Something went wrong!")}
      </span>
      <input
        className="selfofly-error-page__button"
        type_="button"
        value="Auth page"
        onClick={_ => ReasonReactRouter.push("auth")}
      />
      <input
        className="selfofly-error-page__button"
        type_="button"
        value="Main page"
        onClick={_ => ReasonReactRouter.push("main")}
      />
    </div>
  </div>;
};
