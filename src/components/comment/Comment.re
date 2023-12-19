[@react.component]
let make = (~author, ~comment, ~time) => {
  <div className="selfofly-comment">
    <div className="selfofly-comment__header">
      <div className="selfofly-comment__header-text-container">
        <span
          className="selfofly-comment__header-text selfofly-comment__header-text--author">
          {React.string(author)}
        </span>
      </div>
      <span className="selfofly-comment__header-text">
        {React.string(time)}
      </span>
    </div>
    <div className="selfofly-comment__main-container">
      <span className="selfofly-comment__main-text">
        {React.string(comment)}
      </span>
    </div>
  </div>;
};
