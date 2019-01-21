import { Component, OnInit } from '@angular/core';

@Component({
    selector: 'plotly-example',
    template: '<plotly-plot [data]="graph.data" [layout]="graph.layout"></plotly-plot>',
})
export class PlotlyExampleComponent {
    public graph = {
        data: [
            { x: [1, 2, 3], y: [2, 6, 3], type: 'scatter', mode: 'lines+points', marker: {color: 'red'} },
            { x: [1, 2, 3], y: [2, 5, 3], type: 'bar' },
        ],
        layout: {width: 320, height: 240, title: 'A Fancy Plot'}
    };
}

// @Component({
//   selector: 'app-home',
//   templateUrl: './home.component.html',
//   styleUrls: ['./home.component.css']
// })

export class HomeComponent implements OnInit {

  constructor() { }

  ngOnInit() {
  }

}
