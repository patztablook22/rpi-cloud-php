let dir = null
let pos = 0;

document.addEventListener("DOMContentLoaded", () => {

  dir = document.querySelectorAll(".dirItem");
  bindKeys();

  if (dir.length == 0) {
    dir = null;
    return;
  }

  dir.forEach(sniff);
  pos = 0;
  select(0);
});

const sniff = (el) => {
  el.setAttribute("index", pos++);
  el.onmouseover = (e) => {
    select(Number(e.target.getAttribute("index")));
  }
}

const select = index => {
  dir[pos].classList.remove("selected");
  pos = index;
  dir[pos].classList.add("selected");
}

const bindKeys = () => {
  window.onkeydown = keyDown;
}

const keyDown = e => {
  switch (e.key) {
    case "ArrowUp":
      if (dir && pos > 0)
        select(pos - 1);
      break;
    case "ArrowDown":
      if (dir && pos < dir.length - 1)
        select(pos + 1);
      break;
    case "ArrowRight":
    case "Enter":
      if (!dir)
        break;
      window.location = dir[pos].href;
      break;
    case "ArrowLeft":
    case "Backspace":
      let parents = document.querySelectorAll("nav a");
      window.location = parents[parents.length - 2].href;
      break;
    default:
      if (!dir)
        break;
      var first = null;
      var after = null;
      for (let i = 0; i < dir.length; i++) {
        let t = dir[i].innerText;
        if (t[0] == e.key) {
          if (!first)
            first = i;
          if (i > pos) {
            after = i;
            break;
          }
        }
      }
      if (!after)
        after = first;
      if (after)
        select(after);
      break;
  }
}
