---
layout: standalone
permalink: /photoboard
---

# Photoboard
{: .border-bottom  .text-white}

<script>

</script>

<style>
    body {
        background-color: #666;
    }
    .color-0 { color:#941100; }
    .color-1 { color:#4F8F00; }
    .color-2 { color:#005493; }
    .card {
        xmax-width: 200px;
        background-color: #efefef;
        font-size: 90%;
    }
    .card-title {
        text-transform: capitalize;
        font-size: 1.8rem;
        font-weight: 700;
    }
    .card-columns {
        column-count: 4;
      @include media-breakpoint-only(m) {
        column-count: 4;
      }
      @include media-breakpoint-only(xl) {
        column-count: 5;
      }
    }

</style>


{% assign criteria = "f.path contains '" | append: "/photoboard/" | append: "'" %}
{% assign localfiles = site.static_files | where_exp:"f", criteria %}
{% assign bios = localfiles | where:"extname", ".md"  | sort: "basename" %}
{% assign pngs = localfiles | where:"extname", ".png" %}
{% assign jpgs = localfiles | where:"extname", ".jpg" %}
{% assign photos = pngs | concat: jpgs %}

<div class="card-columns">
{% for f in bios %}
{% assign img = photos | where:"basename",f.basename | first %}

<div class="card">
<img class="card-img-top" src="{{img.path}}" alt="Card image">
<div class="card-body p-3">
<p class="card-title">{{f.basename}}</p>
<div class="card-text color-{{forloop.index | modulo: 1 }}" markdown="1">
{% include_relative {{ f.path | remove_first:'/photoboard/' }} %}
</div>
</div>
</div>
{% endfor %}
</div>



